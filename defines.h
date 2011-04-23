/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）
描述：定义数据类型
*/
#ifndef DEFINES_H
#define DEFINES_H

#include <gtk/gtk.h>

#define VERSION "1.07"
#define CSTRING_SIZE 20
#define CSTRING_LENGTH 32
#define PCAP_ERRBUF_SIZE	256
#define PCAP_IF_LOOPBACK	0x00000001
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
typedef unsigned int u_int32_t;
typedef __u_char u_char;
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

typedef struct netType
{
    STRING userName;
    STRING passwd;
    STRING nic;
    u_int32_t ip;
    u_int32_t mask;
    int startMode;
    int dhcpMode;
    u_char localMAC[6];
    u_char destMAC[6];
    char dhcpScript[CSTRING_LENGTH];
}NET;

//全局变量
USER user;      //用户
NET net;
GtkWidget *mainWindow;//主窗口
GtkStatusIcon* trayicon ;//托盘

//调试信息输出
void debug(const char *fileName,const char *functionName,const char *debugInfo);
void guiDebug(const char *fileName,const char *functionName,const char *debugInfo);
void user2net();

#endif
