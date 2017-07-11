#include"head.h"
void ls_server(int new_fd,char *file_name)
{
	DIR *dir;
	dir=opendir(".");
	struct dirent *p;
	struct stat file_stat;
	char path[50];
	char ls_buf[1000]={0};
	int i,len=0;
	if(strlen(file_name)!=2)
	{
		for(i=2;i<strlen(file_name);i++)
		{
			if(file_name[i]!=32)
			{
				send(new_fd,"error input\n",12,0);
				return;
			}	
		}
	}
	while((p=readdir(dir))!=NULL)
	{
		if(p->d_name[0]!='.')
		{
			bzero(path,sizeof(path));		
			sprintf(path,"%s%s","./",p->d_name);
			stat(path,&file_stat);
			sprintf(ls_buf+len,"%9ld bytes\t%s\n",file_stat.st_size,p->d_name);
			len=strlen(ls_buf);
		}
	}
	send(new_fd,ls_buf,strlen(ls_buf),0);
	return;
}
