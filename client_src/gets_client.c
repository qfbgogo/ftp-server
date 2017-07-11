#include"head.h"
void gets_client(int sfd)
{
	int reget;
	reget=-1;//无需续传
	send(sfd,&reget,sizeof(int),0);//告知服务器,本次下载为非续传模式			
	int len;
	char buf[1000]={0};
	recv(sfd,&len,sizeof(int),0);
	if(-1==len)
	{
		printf("download failed!no such file in current diretory.\n");
		return;
	}
	recv(sfd,buf,len,0);
	printf("downloading %s...\n",buf);
	int fd;
	fd=open(buf,O_CREAT|O_RDWR,0664);
	while(1)
	{	
		bzero(buf,sizeof(buf));
		if(len>0)
		{	
			recv_n(sfd,&len,sizeof(int));
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}else{
			printf("download success\n");
			break;
		}
	}
	close(fd);
	return;
}
