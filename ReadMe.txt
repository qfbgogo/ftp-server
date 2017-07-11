ftp服务器项目完成情况汇报：
	1.可以实现一期的所有任务，并新增exit命令退出。
	2.可以实现二期的所有任务，支持断点下载，mmap映射大文件后传送。
	若断点下载的文件是大文件，也可以mmap映射后传送。
	3.实现三期的数据库验证用户信息后登录功能，实现新用户注册功能。
	4.未能实现多点下载功能。

用户登录信息表：create table user_login_info(user_name varchar(50) not null,
		primary key(user_name),
		salt varchar(30) not null,
		passwd varchar(100) not null);
客户端操作日志表：create table op_log(op varchar(50) not null,
		time varchar(35) not null));


