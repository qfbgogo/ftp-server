#include"head.h"
int login_crypt(int sfd)
{
	char *passwd;
	struct spwd *sp;
	char salt[50]={0};
	char usr_name[50]={0};
	int ret,len;
	printf("user name:");
	scanf("%s",usr_name);
	if(send(sfd,usr_name,strlen(usr_name),0)<0)
	{
		perror("send usr_name error");
		return 0;
	}
	passwd=getpass("your password:");
	recv(sfd,&len,sizeof(int),0);
	if(len<=0)
		return len;
	if(recv(sfd,salt,sizeof(salt),0)<=0)
	{
		perror("recv salt error");
		return 0;
	}
	if(send(sfd,crypt(passwd,salt),strlen(crypt(passwd,salt)),0)<0)
	{
		perror("send passwd error");
    	return 0;
	}
	recv(sfd,&len,sizeof(int),0);
	if(len<=0)
		return len;
	if(recv(sfd,&ret,sizeof(int),0)<=0)
	{
		perror("recv ret error");
		return 0;
	}
	return ret;
}	
