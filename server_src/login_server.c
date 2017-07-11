#include"head.h"
void get_salt(char *salt,char *passwd)
{
	int i,j;
	for(i=0,j=0;j<3;i++)
	{
		if(passwd[i]=='$')
			j++;
	}
	strncpy(salt,passwd,i-1);
}
int login_server(int new_fd)
{
	char passwd[100]={0};
	char salt[50]={0};
	char user_name[50]={0};
	int ret;
	if(recv(new_fd,user_name,sizeof(user_name),0)<=0)
	{
		ret=0;
		send(new_fd,&ret,sizeof(int),0);
		return 0;
	}
	if(-1==select_mysql(user_name,passwd))
	{
		printf("no such user!\n");
		ret=-1;
		send(new_fd,&ret,sizeof(int),0);
		return -1;
	}
	get_salt(salt,passwd);
	ret=1;
	send(new_fd,&ret,sizeof(int),0);
	send(new_fd,salt,strlen(salt),0);
	char client_passwd[200]={0};
	if(recv(new_fd,client_passwd,sizeof(client_passwd),0)<=0)
	{
		perror("recv passwd error");
		ret=0;
		send(new_fd,&ret,sizeof(int),0);
		return 0;
	}
	if(strcmp(passwd,client_passwd)==0)
	{
		ret=1;
		send(new_fd,&ret,sizeof(int),0);
		send(new_fd,&ret,sizeof(int),0);
		printf("user %s login success\n",user_name);
		return 1;
	}
	else
	{
		printf("client passwd error\n");
		ret=0;
		send(new_fd,&ret,sizeof(int),0);
		return 0;
	}	
}	
