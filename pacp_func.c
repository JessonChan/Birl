#include <dlfcn.h>
#include "pacp_func.h"

int (*pcap_findalldevs)(pcap_if_t **, char *);
void (*pcap_freealldevs)(pcap_if_t *);
pcap_t *(*pcap_open_live)(const char *, int, int, int, char *);
int (*pcap_compile)(pcap_t *, struct bpf_program *, const char *, int, bpf_u_int32);
int (*pcap_setfilter)(pcap_t *, struct bpf_program *);
char *(*pcap_geterr)(pcap_t *);
void (*pcap_freecode)(struct bpf_program *);
int (*pcap_loop)(pcap_t *, int, pcap_handler, unsigned char *);
void (*pcap_close)(pcap_t *);
void (*pcap_breakloop)(pcap_t *);
int (*pcap_sendpacket)(pcap_t *, const unsigned char *, int);

static void *libpcap = NULL;

int loadLibpcap()
{
    char *error;
    char *file[] = {"libpcap.so", "libpcap.so.1", "libpcap.so.1.0", "libpcap.so.0.9", "libpcap.so.0.8"};
    int i, count = 5;
    for (i=0; i<count && !libpcap; i++)
    {
        libpcap = dlopen(file[i], RTLD_LAZY);
        error = dlerror();
    }
    if (libpcap == NULL)
    {
        debug("pcap_func.c","loadLibpcap","没有找到libpacp的包，你可以试着在其它地方复制libpcap.so到/usr/lib下");
        guiDebug("pcap_func.c","loadLibpcap","没有找到libpacp的包，你可以试着在其它地方复制libpcap.so到/usr/lib下");
        return 0;
    }
    if ((pcap_findalldevs = dlsym(libpcap, "pcap_findalldevs"), error = dlerror()) != NULL
            || (pcap_freealldevs = dlsym(libpcap, "pcap_freealldevs"), error = dlerror()) != NULL
            || (pcap_open_live = dlsym(libpcap, "pcap_open_live"), error = dlerror()) != NULL
            || (pcap_compile = dlsym(libpcap, "pcap_compile"), error = dlerror()) != NULL
            || (pcap_setfilter = dlsym(libpcap, "pcap_setfilter"), error = dlerror()) != NULL
            || (pcap_geterr = dlsym(libpcap, "pcap_geterr"), error = dlerror()) != NULL
            || (pcap_freecode = dlsym(libpcap, "pcap_freecode"), error = dlerror()) != NULL
            || (pcap_loop = dlsym(libpcap, "pcap_loop"), error = dlerror()) != NULL
            || (pcap_close = dlsym(libpcap, "pcap_close"), error = dlerror()) != NULL
            || (pcap_breakloop = dlsym(libpcap, "pcap_breakloop"), error = dlerror()) != NULL
            || (pcap_sendpacket = dlsym(libpcap, "pcap_sendpacket"), error = dlerror()) != NULL)
    {
        debug("pcap_func.c","loadLibpcap","找到libpcap*，但是打不开函数，可能是包损坏了");
        guiDebug("pcap_func.c","loadLibpcap","找到libpcap*，但是打不开函数，可能是包损坏了");
        freeLibpcap();
        return 0;
    }
    else
    {
        debug("pcap_func.c","loadLibpcap","成功打开 libpcap，可以继续进行了");
    }
    return 1;
}

void freeLibpcap()
{
    if (libpcap)
    {
        dlclose(libpcap);
        dlerror();
        libpcap = NULL;
        debug("pcap_func.c","freeLibpcap","成功释放 libpcap＊");
    }
}

int  getNicMsg(CSTRING nicMsg)
{
    debug("pcap_func.c","getNicMsg","开始获得网卡信息");
    pcap_if_t *alldevs, *d;
    int nicNum =0;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, errbuf)==-1 || alldevs==NULL)
    {
        nicNum = 0;
    }
    for (d=alldevs; d!=NULL; d=d->next)
        if (!(d->flags & PCAP_IF_LOOPBACK) && strcmp(d->name, "any")!=0)
        {
            strcpy(nicMsg[nicNum],d->name);
            strcat(nicMsg[nicNum],"\0");
            nicNum++;
            debug("pcap_func.c","getNicMsg",d->name);
        }
    return nicNum;
}
