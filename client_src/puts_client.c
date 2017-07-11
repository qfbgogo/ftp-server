#include"head.h"
void puts_client(int sfd,char *file_name)
{
	train t;
	bzero(&t,sizeof(t));
	if(is_file_exist(file_name))
	{	
		printf("uploading %s...\n",file_name);
		strcpy(t.buf,file_name);
		t.len=strlen(file_name);
		send(sfd,&t,t.len+4,0);
		//发送文件内容
		int fd;
		fd=open(file_name,O_RDWR);
		bzero(&t,sizeof(t));
		while((t.len=read(fd,t.buf,sizeof(t.buf)))>0)
		{
			if(-1==send_n(sfd,&t,4+t.len))
			{
				printf("server drop upload\n");
				close(sfd);
				close(fd);
				return;
			}
		}
		//发送结束符
		t.len=0;
		send(sfd,&t.len,sizeof(int),0);
		printf("upload success\n");
		//关闭描述符
		close(fd);
		return;
	}else{
		t.len=-1;//当前目录没有要上传的文件
		send(sfd,&t,sizeof(int),0);
		printf("upload failed!no such file to upload.\n");
	}
	return;
}
