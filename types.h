/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）木瓜无衣 （1401570404@qq.com)

*/
#ifndef TYPES_H
#define TYPES_H
typedef unsigned char *POINTER;
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef unsigned short int WORD;
typedef int LONG;
typedef unsigned int DWORD;
typedef unsigned int UINT4;
#define CSTRING_SIZE 20
#define CSTRING_LENGTH 32
#define ARGC 3
typedef char CSTRING[CSTRING_SIZE][CSTRING_LENGTH];
typedef char ARGV [ARGC][CSTRING_LENGTH];


#define EXIT_FAILURE -1
#define EXIT_SUCCESS 1

#define VERSION "1.06.1"
#define ICO_PATH DATA_INSTALL_DIR"/birl/birl.ico"
#define ABOUT_ICO DATA_INSTALL_DIR"/birl/birl_about.ico"
#define BACKIMAGE_PATH DATA_INSTALL_DIR"/birl/backimage.jpeg"
#define INTERNET_PATH DATA_INSTALL_DIR"/birl/internet.png"
#define D_DHCPSCRIPT  "dhclient %s>/dev/null 2>&1"		/* 默认DHCP脚本 */
#define CFG_FILE  DATA_INSTALL_DIR"/birl/birl.cfg"		/* 配置文件 */
//static const char *LOG_FILE = "/tmp/bril.log";		/* 日志文件 */
#define LOCK_FILE  "/var/run/mentohust.pid"	/* 锁文件 */
#endif
