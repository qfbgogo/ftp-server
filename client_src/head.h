#include<shadow.h>
#include<crypt.h>
#include<time.h>
#include<ctype.h>
#include<signal.h>
#include<strings.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/uio.h>
#include<sys/stat.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<dirent.h>
typedef struct child{
		pid_t pid;//子进程pid
		int fdw;//管道写端
		short busy;//判断进程是否忙碌
}cdata,*pcdata;
typedef struct sendfile{
	int len;
	char buf[1000];
}train,*ptrain;
void childprocs_make(pcdata,int);
void send_fd(int,int);
void recv_fd(int,int *);
void handle_request(int);
