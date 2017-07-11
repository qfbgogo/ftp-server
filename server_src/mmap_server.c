#include"head.h"

int mmap_server(int new_fd,char *file_name,long reget)
{
	time_t tt;
	struct stat fstat;
    char path[50]={0};
    sprintf(path,"%s%s","./",file_name);
    stat(path,&fstat);
    long offset;
    offset=fstat.st_size;
	long remain=offset-reget;
	if(remain<=104857600)//文件小于100M无需mmap
		return 0;
	printf("%s>100M,begin mmap...\n",file_name);
	time_print2log("filesize>100M,begin mmap send",tt);
	int fd;
    fd=open(file_name,O_RDWR);
	char *mstart,*p;
	mstart=(char *)mmap(NULL,offset,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	mstart=mstart+reget;
	p=mstart;
	long sum=0;
	int len=1000;
	long rest;
	while(sum<remain)
	{
		rest=remain-sum;
		if(rest>0&&rest<1000)
		{
			send_n(new_fd,&rest,sizeof(long));
			send_n(new_fd,mstart,rest);
			break;
		}
		if(-1==send_n(new_fd,&len,sizeof(int)))
        {
             printf("client drop download\n");
			 time_print2log("client drop download",tt);
             close(new_fd);
             close(fd);
             return 0;
        }
		if(-1==send_n(new_fd,mstart,len))
        {
             printf("client drop download\n");
			 time_print2log("client drop download",tt);
             close(new_fd);
             close(fd);
             return 0;
        }
		mstart=mstart+len;
		sum=sum+len;
	}
	len=0;
	send(new_fd,&len,sizeof(int),0);
	printf("client mmap download %s success\n",file_name);
	time_print2log("client mmap download success",tt);
	close(fd);
	munmap(p,offset);
	return 1;
}
