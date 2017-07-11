#include"head.h"
int select_mysql(char *user_name,char *passwd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="0105";
	char* database="mydata";
	char* query="select * from user_login_info";
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)//行数
			{
				if(strcmp(row[0],user_name)==0)
					{
						strcpy(passwd,row[2]);	
						return 1;
					}
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return -1;
}
