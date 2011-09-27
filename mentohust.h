/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）
*/


#ifndef MENTOHUST_H
#define MENTOHUST_H

//用来保持联网
int mentohust();
//开始连网，用户名，密码，环境变量
void startConnect(const char *,const char *,ARGV);
int statasConnect();
char *getServerMsg();
void saveConfig();
void endConnect();
gpointer keepConnect();
#endif
