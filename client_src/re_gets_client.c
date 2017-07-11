#include"head.h"
void re_gets_client(int sfd,char *filename)
{
	struct stat fstat;
	char path[50]={0};
	sprintf(path,"%s%s","./",filename);
	stat(path,&fstat);
	long offset;
	offset=fstat.st_size;
	send(sfd,&offset,sizeof(long),0);
	int fd;
	fd=open(filename,O_RDWR|O_APPEND);
	int len;
	char buf[1000];
	printf("continue download %s...\n",filename);
	while(1)
    {
          bzero(buf,sizeof(buf));
          recv_n(sfd,&len,sizeof(int));
          if(len>0)
          {
              recv_n(sfd,buf,len);
              write(fd,buf,len);
          }else if(len==0){
              printf("download success\n");
              break;
          }else if(len==-1){
				printf("download failed,no such file!\n");
		  }
    }
    close(fd);
}
