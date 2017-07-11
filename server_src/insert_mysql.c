#include"head.h"
int insert_mysql_login(char *user_name,char *salt,char *passwd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="0105";
	char* database="mydata";
	char query[300]={0};
	sprintf(query,"insert into user_login_info(user_name,salt,passwd) values('%s','%s','%s')",user_name,salt,passwd);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}
	t=mysql_query(conn,query);
	if(t)
    {
       return -1;//用户已经存在，注册失败
    }else{
        printf("insert new user info to mysql success\n");
    }
    mysql_close(conn);
	return 1;
}
void insert_mysql_op(char *op,char *time)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="0105";
	char* database="mydata";
	char query[200]={0};
	sprintf(query,"insert into op_log(op,time) values('%s','%s')",op,time);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}
	t=mysql_query(conn,query);
	mysql_close(conn);
	return;
}
