/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）
描述：定义数据类型
*/
#ifndef DEFINES_H
#define DEFINES_H

#define VERSION "1.07"
#define CSTRING_SIZE 20
#define CSTRING_LENGTH 32
#define ICO_PATH "/opt/birl/birl.ico"
#define ABOUT_ICO "/opt/birl/birl_about.ico"
#define BACKIMAGE_PATH "/opt/birl/backimage.jpeg"
#define INTERNET_PATH "/opt/birl/internet.png"
#define D_DHCPSCRIPT  "dhclient %s>/dev/null 2>&1"
#define CFG_FILE  "/opt/birl/birl.cfg"
#define LOG_FILE  "/tmp/birl.log"


typedef unsigned char *POINTER;
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned short int WORD;
typedef int LONG;
typedef unsigned int DWORD;
typedef unsigned int UINT4;
typedef char CSTRING[CSTRING_SIZE][CSTRING_LENGTH];
typedef char STRING [CSTRING_LENGTH];

typedef struct userType
{
    STRING userName;
    STRING passwd;
    STRING nic;
    STRING startMode;
    STRING dhcpMode;
    STRING ip;
    STRING mask;
} USER;

//全局变量
USER user;      //用户
#endif
