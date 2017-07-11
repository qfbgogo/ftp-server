#include"head.h"
void create_salt(char s[],char salt[])
{
	int num=8;
	char *str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz/,.?";
 	int i,lstr;
 	char ss[2] = {0};
 	lstr = strlen(str);
 	srand((unsigned int)time((time_t *)NULL));
 	for(i = 1; i <= num; i++){
  	{	
		sprintf(ss,"%c",str[(rand()%lstr)]);
 	 	strcat(s,ss);
	}
	sprintf(salt,"$6$%s",s);
	}
}
int register_crypt(int sfd)
{
	char salt[12]={0};
	char s[9]={0};
	create_salt(s,salt);
	char *passwd;
	char user_name[30]={0};
	printf("new user name:");
	scanf("%s",user_name);
	passwd=getpass("new password:");
	int len=strlen(user_name);
	send(sfd,&len,sizeof(int),0);
	send(sfd,user_name,len,0);
	len=strlen(crypt(passwd,salt));
	send(sfd,&len,sizeof(int),0);
	send(sfd,crypt(passwd,salt),len,0);
	int res;
	recv(sfd,&res,sizeof(int),0);
	if(res<0)
	{
		printf("sorry,register failed.user %s exist\n",user_name);
		return -1;
	}else{
		printf("register success\n");
		return 1;
	}
}
