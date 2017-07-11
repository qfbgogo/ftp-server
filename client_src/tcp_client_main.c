#include"head.h"
int main(int argc,char *argv[])
{
	if(3!=argc)
	{
		perror("error args");
		return -1;
	}
	int sfd;
	int ret;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("error socket");
		return -1;
	}
	struct sockaddr_in ser_addr;
	memset(&ser_addr,0,sizeof(struct sockaddr_in));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_port=htons(atoi(argv[2]));
	ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if(-1==connect(sfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr)))
	{
		perror("error connect");
		close(sfd);
		return -1;
	}else{
		printf("connect success\n");
	}
	int log_or_reg;
	printf("1.login  2.register\n");
	printf("your choice:");
	scanf("%d",&log_or_reg);
	send(sfd,&log_or_reg,sizeof(int),0);
	if(1==log_or_reg)
	{
		ret=login_crypt(sfd);
		while(ret<0)
		{
			printf("login failed,user's name or passwd wrong\n");
			ret=login_crypt(sfd);
		}
		printf("login success\n");
	}else if(2==log_or_reg){
		ret=register_crypt(sfd);
		while(ret<0)
		{
			ret=register_crypt(sfd);
		}
	}else{
		close(sfd);
		printf("error input\n");
		return 0;
	}
	int i;
	char file_name[20];
	train t;
	bzero(&t,sizeof(t));
	while(1)
	{
		bzero(t.buf,sizeof(t.buf));
		t.len=read(0,t.buf,sizeof(t.buf))-1;//去掉换行符
		if(strncmp(t.buf,"exit",4)==0)
		{
			printf("logout\n");
			break;
		}	
		send(sfd,&t,4+t.len,0);
		if(strncmp(t.buf,"gets",4)==0)
		{
            bzero(file_name,sizeof(file_name));
            for(i=0;i<sizeof(t.buf);i++)
            {
                if(t.buf[i]==32&&t.buf[i+1]!=32)
                    {
                      strncpy(file_name,t.buf+i+1,t.len-i-1);//去换行
                      break;
                   }
            }
			if(0==is_file_exist(file_name))//文件不存在
				gets_client(sfd);
			else //文件已经存在,进行断点续传
				re_gets_client(sfd,file_name);
		}
		if(strncmp(t.buf,"puts",4)==0)
        {
            bzero(file_name,sizeof(file_name));
            for(i=0;i<sizeof(t.buf);i++)
            {
                if(t.buf[i]==32&&t.buf[i+1]!=32)
                    {
                      strncpy(file_name,t.buf+i+1,t.len-i-1);//去换行
                      break;
                   }
            }
            puts_client(sfd,file_name);
       }
	   if(strncmp(t.buf,"ls",2)==0)
	   {
			char ls_buf[1000]={0};
			recv(sfd,ls_buf,sizeof(ls_buf),0);
			fflush(stdout);
			printf("%s",ls_buf);
		}
	   if(strncmp(t.buf,"remove",6)==0)
		{
			recv(sfd,&ret,sizeof(int),0);
			if(ret==0)
			{
				printf("remove success\n");
			}else{
				printf("remove failed,no such file!\n");
			}
		}
		if(strncmp(t.buf,"cd",2)==0)
		{
			recv(sfd,&ret,sizeof(int),0);
			if(ret==0)
			{
				printf("cd success\n");
			}else{
				printf("cd failed,no such diretory!\n");
			}
			
		}
		if(strncmp(t.buf,"pwd",3)==0)
		{
			char pwd_buf[50]={0};
			recv(sfd,pwd_buf,sizeof(pwd_buf),0);
			printf("%s\n",pwd_buf);
		}		
	}
	close(sfd);
	return 0;
}
