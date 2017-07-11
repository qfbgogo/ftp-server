#include"head.h"
void time_print2log(char *op_buf,time_t tt)
{
	int fd;
	fd=open("client.log",O_CREAT|O_APPEND|O_RDWR,0644);
	time(&tt);//获取当前秒数时间	
	char time_buf1[35]={0};
	char time_buf2[35]={0};
	strcpy(time_buf1,ctime(&tt));
	strncpy(time_buf2,ctime(&tt),strlen(ctime(&tt))-1);//去换行符
	char buf[200]={0};
	sprintf(buf,"%s\t%s",op_buf,time_buf1);
	insert_mysql_op(op_buf,time_buf2);
	write(fd,buf,strlen(buf));
	close(fd);
}
