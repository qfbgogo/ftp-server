#include"head.h"

int main(int argc,char *argv[])
{
	if(2!=argc)
	{
		perror("args error");
		return -1;
	}
	signal(SIGPIPE,SIG_IGN);
	time_t tt;
	char *conf_buf[3];
	conf(argv[1],conf_buf);
	int num=atoi(conf_buf[2]);
	pcdata pchild;
	pchild=(pcdata)calloc(num,sizeof(cdata));
	childprocs_make(pchild,num);
	int i,j,ret;
	int sfd,new_fd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in myaddr;
	struct sockaddr_in clientaddr;
	char client_socket[30]={0};
	int addrlen=sizeof(struct sockaddr);
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(atoi(conf_buf[1]));
	myaddr.sin_addr.s_addr=inet_addr(conf_buf[0]);
	if(-1==bind(sfd,(struct sockaddr *)&myaddr,sizeof(struct sockaddr)))
	{
		perror("bind error");
		return -1;
	}
	ret=listen(sfd,num);
	if(ret<0)
	{
		perror("listen error");
		return -1;
	}
	int temp;//在socketpair生成的两个描述符(peer)内通信
	int epfd;
	epfd=epoll_create(1);
	struct epoll_event event,*evs;
	bzero(&event,sizeof(struct epoll_event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	evs=(struct epoll_event *)calloc(num+1,sizeof(struct epoll_event));
	for(i=0;i<num;i++)
	{
		event.events=EPOLLIN;
		event.data.fd=pchild[i].fdw;
		epoll_ctl(epfd,EPOLL_CTL_ADD,pchild[i].fdw,&event);
	}
	while(1)
	{	
		bzero(evs,(num+1)*sizeof(struct epoll_event));
		ret=epoll_wait(epfd,evs,num+1,-1);
		if(ret>0)
		{
			for(i=0;i<ret;i++)
			{
				if(evs[i].data.fd==sfd)//客户端请求连接
				{
					new_fd=accept(sfd,(struct sockaddr *)&clientaddr,&addrlen);
					sprintf(client_socket,"%s %d connect",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
					time_print2log(client_socket,tt);
					for(j=0;j<num;j++)
					{
						if(pchild[j].busy==0)
						{
							printf("childproc %d will be busy\n",pchild[j].pid);
							send_fd(pchild[j].fdw,new_fd);	
							pchild[j].busy=1;
							break;
						}
					}
					close(new_fd);
				}
				for(j=0;j<num;j++)
				{
					if(evs[i].data.fd==pchild[j].fdw)
					{
						read(pchild[j].fdw,&temp,sizeof(temp));			
						printf("childproc %d is idle\n",pchild[j].pid);
						pchild[j].busy=0;//子进程空闲
					}
				}
			}
		}
	}
	close(new_fd);
	close(sfd);
	return 0;
}
