/* -*- Mode: C; tab-width: 4; -*- */
/*
* Copyright (C) 2009, HustMoon Studio
*
* 文件名称：myconfig.c
* 摘	要：初始化认证参数
* 作	者：HustMoon@BYHH
* 邮	箱：www.ehust@gmail.com
*/

#include "myconfig.h"
#include "myini.h"
#include "myfunc.h"
#include "dlfunc.h"
#include "types.h"
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#define ACCOUNT_SIZE		65	/* 用户名密码长度*/
#define NIC_SIZE			16	/* 网卡名最大长度 */
#define MAX_PATH			255	/* FILENAME_MAX */
#define D_TIMEOUT			8	/* 默认超时间隔 */
#define D_ECHOINTERVAL		20	/* 默认心跳间隔 */
#define D_RESTARTWAIT		15	/* 默认重连间隔 */
#define D_STARTMODE			0	/* 默认组播模式 */
#define D_DHCPMODE			0	/* 默认DHCP模式 */
#define D_DAEMONMODE		0	/* 默认daemon模式 */
#define D_MAXFAIL			0	/* 默认允许失败次数 */

#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)	/* 创建掩码 */


extern int bufType;	/*0内置xrgsu 1内置Win 2仅文件 3文件+校验*/
extern u_char version[];	/* 版本 */
char userName[ACCOUNT_SIZE] = "";	/* 用户名 */
char password[ACCOUNT_SIZE] = "";	/* 密码 */
char nic[NIC_SIZE] = "";	/* 网卡名 */
char dataFile[MAX_PATH] = "";	/* 数据文件 */
char dhcpScript[MAX_PATH] = "";	/* DHCP脚本 */
u_int32_t ip = 0;	/* 本机IP */
u_int32_t mask = 0;	/* 子网掩码 */
u_int32_t gateway = 0;	/* 网关 */
u_int32_t dns = 0;	/* DNS */
u_int32_t pingHost = 0;	/* ping */
u_char localMAC[6];	/* 本机MAC */
u_char destMAC[6];	/* 服务器MAC */
unsigned timeout = D_TIMEOUT;	/* 超时间隔 */
unsigned echoInterval = D_ECHOINTERVAL;	/* 心跳间隔 */
unsigned restartWait = D_RESTARTWAIT;	/* 失败等待 */
unsigned startMode = D_STARTMODE;	/* 组播模式 */
unsigned dhcpMode = D_DHCPMODE;	/* DHCP模式 */
unsigned maxFail = D_MAXFAIL;	/* 允许失败次数 */
pcap_t *hPcap = NULL;	/* Pcap句柄 */
int lockfd = -1;	/* 锁文件描述符 */

static void readArg(ARGV argv);	/* 读取命令行参数来初始化 */
static int openPcap();	/* 初始化pcap、设置过滤器 */
static void checkRunning(int exitFlag);	/* 检测是否已运行 */

void initArgv(ARGV argv)
{
    strcpy(nic,argv[0]);
    if(!strcmp(argv[1],"标准"))
        startMode=0;
    else if(!strcmp(argv[1],"锐捷"))
        startMode=1;
    if(!strcmp(argv[2],"无"))
        dhcpMode=0;
    else if(!strcmp(argv[2],"二次认证"))
        dhcpMode=1;
    else if(!strcmp(argv[2],"认证前"))
        dhcpMode=3;
    else if(!strcmp(argv[2],"认证后"))
        dhcpMode=2;
    //  ip=atoi(argv[3]);
    //  mask=atoi(argv[4]);
    printf("All the need config Got!!,%d,%d\n",startMode,dhcpMode);
}
void initConfig(char *name, char *passwd,ARGV argv)
{
    int saveFlag = 0;	/* 是否需要保存参数 */
    int exitFlag = 0;	/* 0Nothing 1退出 2重启 */
    strcpy(userName,name);
    strcpy(password,passwd);
    initArgv(argv);
    // checkRunning(exitFlag);
    if (startMode%3==2 && gateway==0)	/* 赛尔且未填写网关地址 */
    {
        gateway = ip;	/* 据说赛尔的网关是ip前三字节，后一字节是2 */
        ((u_char *)&gateway)[3] = 0x02;
    }
    if(strstr(dhcpScript,"dhclient"))
    {
        dhcpScript[0]='\0';
        sprintf(dhcpScript,D_DHCPSCRIPT,nic);
    }

    if (dhcpScript[0] == '\0')	/* 未填写DHCP脚本？ */
    {
        sprintf(dhcpScript,D_DHCPSCRIPT,nic);
    }
    newBuffer();
    printf("进入fillHeader,打开过滤\n");
    if(fillHeader()==-1)
    {
        printf("fillHear,Done\n");
        exit(-1);
    }
    if(openPcap()==-1)
    {
        printf("OpenPcap failed\n");
        exit(-1);
    }
}

static int openPcap()
{
    char buf[PCAP_ERRBUF_SIZE], *fmt;
    struct bpf_program fcode;
    printf("Hill,%s\n",nic);
    if ((hPcap = pcap_open_live(nic, 2048, 1, 1000, buf)) == NULL)
    {
        printf("网卡%s打开失败，请重新设置: %s\n", nic, buf);
        return -1;
    }
    printf("Hill,%s\n",nic);
    fmt = formatHex(localMAC, 6);
    sprintf(buf, "ether proto 0x888e and (ether dst %s or ether dst 01:80:c2:00:00:03) "
            "and not ether src %s", fmt, fmt);
    if (pcap_compile(hPcap, &fcode, buf, 0, 0xffffffff) == -1
            || pcap_setfilter(hPcap, &fcode) == -1)
    {
        printf("pcap无法过滤: %s\n", pcap_geterr(hPcap));
        return -1;
    }
    pcap_freecode(&fcode);
    return 0;
}

static void checkRunning(int exitFlag)
{
    struct flock fl;
    lockfd = open (LOCK_FILE, O_RDWR|O_CREAT, LOCKMODE);
    if (lockfd < 0)
    {
        perror("!! 打开锁文件失败");	/* perror真的很好啊，以前没用它真是太亏了 */
        goto error_exit;
    }
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    fl.l_type = F_WRLCK;
    if (fcntl(lockfd, F_GETLK, &fl) < 0)
    {
        perror("!! 获取文件锁失败");
        goto error_exit;
    }
    if (exitFlag)
    {
        if (fl.l_type != F_UNLCK)
        {
            printf(">> 已发送退出信号给Birl进程(PID=%d).\n", fl.l_pid);
            if (kill(fl.l_pid, SIGINT) == -1)
                perror("!! 结束进程失败");
        }
        else
            printf("!! 没有Birl正在运行！\n");
        if (exitFlag == 1)
            exit(EXIT_SUCCESS);
    }
    else if (fl.l_type != F_UNLCK)
    {
        fl.l_type = F_WRLCK;
        fl.l_pid = getpid();
        if (fcntl(lockfd, F_SETLKW, &fl) < 0)
        {
            perror("!! 加锁失败");
            goto error_exit;
        }
    }
    return;

error_exit:
    exit(EXIT_FAILURE);
}
