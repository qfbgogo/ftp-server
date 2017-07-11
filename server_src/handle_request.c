#include"head.h"

void handle_request(int new_fd)
{
	time_t tt;
	int i,j,ret;
	long reget;
	char file_name[20];
	train t;
	bzero(&t,sizeof(t));
	int log_or_reg;
	recv(new_fd,&log_or_reg,sizeof(int),0);
	if(1==log_or_reg)
	{
		ret=login_server(new_fd);
		if(ret==0)
			return;
		while(ret<0)
		{
			printf("client login failed\n");
			time_print2log("client login failed",tt);
			ret=login_server(new_fd);
			if(ret==0)
				return;
		}
		time_print2log("client login success",tt);
	}else if(2==log_or_reg){
		ret=register_server(new_fd);
		if(ret==0)
			return;
		while(ret<0)
		{
			printf("user exist,register failed\n");
			time_print2log("user exist,register failed",tt);
			ret=register_server(new_fd);
			if(ret==0)
				return;
		}
		time_print2log("client register success",tt);
	}else{
		return;
	}		
	while(recv(new_fd,&t.len,sizeof(int),0)>0)
	{
		bzero(t.buf,sizeof(t.buf));
		recv(new_fd,t.buf,t.len,0);
		time_print2log(t.buf,tt);
		if(strncmp(t.buf,"gets",4)==0)
		{
			bzero(file_name,sizeof(file_name));
			for(i=0;i<sizeof(t.buf);i++)
			{
				if(t.buf[i]==32&&t.buf[i+1]!=32)	
					{
						strcpy(file_name,t.buf+i+1);
						break;
					}
			}
			recv(new_fd,&reget,sizeof(long),0);//用来判断是否需要断点续传	
			gets_server(new_fd,file_name,reget);
		}
		if(strncmp(t.buf,"puts",4)==0)
		{
			puts_server(new_fd);
		}
		if(strncmp(t.buf,"ls",2)==0)
		{
			ls_server(new_fd,t.buf);
		}
		if(strncmp(t.buf,"remove",6)==0)
		{
			bzero(file_name,sizeof(file_name));
			for(i=0;i<sizeof(t.buf);i++)
			{
				if(t.buf[i]==32&&t.buf[i+1]!=32)	
					{
						strcpy(file_name,t.buf+i+1);
						break;
					}
			}
			ret=remove(file_name);
			send(new_fd,&ret,sizeof(int),0);
		}
		if(strncmp(t.buf,"cd",2)==0)
		{
			char dir_name[20]={0};
			for(i=0;i<sizeof(t.buf);i++)
			{
				if(t.buf[i]==32&&t.buf[i+1]!=32)	
					{
						strcpy(dir_name,t.buf+i+1);
						break;
					}
			}
			ret=chdir(dir_name);
			send(new_fd,&ret,sizeof(int),0);
		}
		if(strncmp(t.buf,"pwd",3)==0)
		{
			pwd_server(new_fd,t.buf);		
		}
	}
}
