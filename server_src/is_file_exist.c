#include"head.h"
int is_file_exist(char *filename)
{
	DIR *dir;
	dir=opendir(".");
	struct dirent *p;
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,filename)==0)
		{
			closedir(dir);
			return 1;
		}
	}
	closedir(dir);
	return 0;
}
