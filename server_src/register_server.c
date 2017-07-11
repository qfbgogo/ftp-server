#include"head.h"
int register_server(int new_fd)
{
	//struct spwd sp;
	//bzero(&sp,sizeof(sp));
	//sp.sp_namp=(char *)malloc(30);
	//sp.sp_pwdp=(char *)malloc(100); 
	char passwd[100]={0};
	char salt[30]={0};
	char user_name[30]={0};
	int len;
	time_t tt;
	if(recv(new_fd,&len,sizeof(int),0)<=0)
	{
		time_print2log("client drop register",tt);
		return 0;		
	}
	recv(new_fd,user_name,len,0);
	recv(new_fd,&len,sizeof(int),0);
	recv(new_fd,passwd,len,0);
	//strcpy(sp.sp_namp,user_name);
	//strcpy(sp.sp_pwdp,passwd);
	//FILE *fp;
	//fp=fopen("/etc/shadow","ab+");
	//putspent(&sp,fp);
	//fclose(fp);
	get_salt(salt,passwd);
	int res=insert_mysql_login(user_name,salt,passwd);
	send(new_fd,&res,sizeof(res),0);
	if(res==1)
		return 1;
	else if(res==-1)
		return -1;
}
