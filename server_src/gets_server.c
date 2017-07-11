#include"head.h"
void gets_server(int new_fd,char *file_name,long reget)
{
	if(-1==reget)
	{
		time_t tt;
		train t;
		bzero(&t,sizeof(t));
		if(is_file_exist(file_name))
		{	
			//发送文件名
			printf("client downloading %s...\n",file_name);
			time_print2log("client downloading",tt);
			strcpy(t.buf,file_name);
			t.len=strlen(file_name);
			send(new_fd,&t,t.len+4,0);
			//发送文件内容
			if(mmap_server(new_fd,file_name,0)>0)//mmap发送
				return;
			int fd;
			fd=open(file_name,O_RDWR);
			bzero(&t,sizeof(t));
			while((t.len=read(fd,t.buf,sizeof(t.buf)))>0)
			{
				if(-1==send_n(new_fd,&t,4+t.len))
				{
					close(new_fd);
					close(fd);
					return;
				}
			}
			//发送结束符
			t.len=0;
			send(new_fd,&t.len,sizeof(int),0);
			printf("download %s success\n",file_name);
			time_print2log("download success",tt);
			//关闭描述符
			close(fd);
			return;
		}else{
			t.len=-1;//当前目录没有要下载的文件
			send(new_fd,&t.len,sizeof(int),0);
			return;
		}
	}else{
		time_t tt;
		printf("client continue downloading %s...\n",file_name);
		time_print2log("client continue downloading",tt);
		if(mmap_server(new_fd,file_name,reget)>0)
			return;
		int fd;
		fd=open(file_name,O_RDWR);	
		lseek(fd,reget,SEEK_SET);
		train t;
		bzero(&t,sizeof(t));
		while((t.len=read(fd,t.buf,sizeof(t.buf)))>0)
		{
			if(-1==send_n(new_fd,&t,4+t.len))
			{
				printf("client drop download\n");
				time_print2log("client drop download",tt);
				close(new_fd);
				close(fd);
				return;
			}
		}
		//发送结束符
		t.len=0;
		send(new_fd,&t.len,sizeof(int),0);
		printf("download %s success\n",file_name);
		time_print2log("download success",tt);
		//关闭描述符
		close(fd);
		return;
	}
}
