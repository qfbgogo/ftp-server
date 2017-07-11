#include"head.h"  
void conf(char *path,char *conf_buf[])
{
    FILE *pfile;
    pfile=fopen(path,"rb+");
    char info_buf[50]={0};
    fgets(info_buf,sizeof(info_buf),pfile);
    int i,j,m=0;
    for(i=0,j=0;i<strlen(info_buf);i++)
    {
       if(info_buf[i]==32||info_buf[i]==0||info_buf[i]==10)
        {
            conf_buf[j]=(char *)malloc(m+1);
            strncpy(conf_buf[j],info_buf+i-m,m);
            j++;m=0;
        }else{
            m++;
        }
    }
	fclose(pfile);
}

