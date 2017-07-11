#include"head.h"
void pwd_server(int new_fd,char *file_name)
{
	int i;
	if(strlen(file_name)!=2)
	{
		for(i=3;i<strlen(file_name);i++)
		{
			if(file_name[i]!=32)
			{
				send(new_fd,"error input\n",12,0);
				return;
			}	
		}
	}
	char pwd[50]={0};
	getcwd(pwd,sizeof(pwd));
	send(new_fd,pwd,strlen(pwd),0);
	return;
}
