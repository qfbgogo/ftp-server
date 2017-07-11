#include"head.h"
void puts_server(int new_fd)
{
	time_t tt;
	int len;
	char buf[1000]={0};
	recv(new_fd,&len,sizeof(int),0);
	if(-1==len)
	{
		return;
	}
	recv(new_fd,buf,len,0);
	printf("client uploading %s...\n",buf);
	time_print2log("client uploading",tt);
	int fd;
	fd=open(buf,O_CREAT|O_RDWR,0664);
	while(1)
	{	
		bzero(buf,sizeof(buf));
		if(len>0)
		{	
			if(recv_n(new_fd,&len,sizeof(int))<=0)
			{
				perror("secv_n len error");
				time_print2log("client uploading failed!",tt);
				break;
			}
			if(recv_n(new_fd,buf,len)<=0)
			{
				perror("secv_n buf,len");
				time_print2log("client uploading failed!",tt);
				break;
			}
			if(-1==write(fd,buf,len))
			{
				perror("write error");
				break;
			}
		}else{
			printf("upload success\n");
			time_print2log("upload success",tt);
			break;
		}
	}
	close(fd);
	return;
}
