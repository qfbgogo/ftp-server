#include"head.h"
int  send_n(int sfd,char *buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=send(sfd,buf+total,len-total,0);
		if(ret<0)
		{
			perror("client exited");
			return -1;
		}
		total=ret+total;
	}
	return 0;
}
int recv_n(int sfd,char *buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=recv(sfd,buf+total,len-total,0);
		if(ret<0)
		{
			perror("server exited");
			return -1;
		}
			total=ret+total;
	}
	return 0;
}
