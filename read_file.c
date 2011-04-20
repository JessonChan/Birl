#include <string.h>
#include <stdio.h>

#include "defines.h"
#include "read_file.h"

extern USER user;
static void encodePass(char *);
static void decodePass(char *);


void encodePass(char *str)
{
    int i = strlen(str);
    for(; i>0; i--)
    {
        str[i-1]=str[i-1]+i;
        str[i-1]^=(i-1);
    }
}

void decodePass(char *str)
{

    int i = strlen(str);
    for(; i>0; i--)
    {
        str[i-1]^=(i-1);
        str[i-1]=str[i-1]-i;
    }
}

int readFile()
{
    FILE *fp = NULL;
    char tmp[32];
    if ((fp=fopen(LOG_FILE, "r")) == NULL)
        return 0;
    fgets(tmp,255,fp);//这是第一行的[birl]
    if(!strcmp(tmp,"[first]\n"))
    {
        debug("read_file.c","readFile","这是第一次运行程序");
        guiDebug("read_file.c","readFile","这是第一次运行程序,请一定要进行设置哟~方法可以在设置->帮助里找到的");
    }
    fscanf(fp,"%s",user.userName);
    fscanf(fp,"%s",tmp);//密码
    decodePass(tmp);
    sprintf(user.passwd,"%s",tmp);
    fscanf(fp,"%s",user.nic);//网卡
    fscanf(fp,"%s",tmp);//startmode
    strcpy(user.startMode,strcmp(tmp,"Standerd")==0?"标准":(strcmp(tmp,"Ruijie")==0?"锐捷":"赛尔"));
    fscanf(fp,"%s",tmp);//dhcpmode
    strcpy(user.dhcpMode,strcmp(tmp,"None")==0?"静态":strcmp(tmp,"Double")==0?"二次认证":strcmp(tmp,"Before")==0?"认证前":"认证后");
    fscanf(fp,"%s",user.ip);
    fscanf(fp,"%s",user.mask);
    fclose(fp);
    return 1;
}

int saveFile()
{
    FILE *fp;
    int result;
    if ((fp=fopen(LOG_FILE, "w")) == NULL)
        return 0;
    encodePass(user.passwd);
    result = fprintf(fp,"[Birl]\n%s\n%s\n%s\n%s\n%s\n%s\n%s",user.userName,user.passwd,user.nic,user.startMode,user.dhcpMode,user.ip,user.mask);
    decodePass(user.passwd);
    fclose(fp);
    return result;
}
