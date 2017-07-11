#include"head.h"
void child_handle(int fdr)
{
	time_t tt;
	int temp=1;//在socketpair生成的两个描述符内通信
	int new_fd;
	while(1)
	{
		recv_fd(fdr,&new_fd);//等待父进程发送任务
		handle_request(new_fd);//向客户机端发送文件
		write(fdr,&temp,sizeof(temp));//向父进程发送任务完成
		time_print2log("logout",tt);	
	}
}
void childprocs_make(pcdata p,int num)
{
	int i,fds[2];
	pid_t pid;
	for(i=0;i<num;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(0==pid)
		{
			close(fds[1]);
			child_handle(fds[0]);
		}
		close(fds[0]);
		p[i].pid=pid;
		p[i].fdw=fds[1];
		p[i].busy=0;
	}
}
