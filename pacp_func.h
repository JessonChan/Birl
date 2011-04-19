#ifndef PCAP_FUNC_H
#define PCPA_FUNC_H

#include "defines.h"

#include <stdio.h>
#include <string.h>
#include <sys/time.h>


typedef unsigned int bpf_u_int32;
typedef void pcap_t;
typedef struct pcap_if
{
    struct pcap_if *next;
    char *name;
    char *description;
    void *addresses;
    bpf_u_int32 flags;
} pcap_if_t;
struct bpf_program
{
    unsigned int bf_len;
    void *bf_insns;
};
struct pcap_pkthdr
{
    struct timeval ts;
    bpf_u_int32 caplen;
    bpf_u_int32 len;
};
typedef void (*pcap_handler)(unsigned char *, const struct pcap_pkthdr *, const unsigned char *);

int  getNicMsg(CSTRING nicMsg);
void freeLibpcap();
int loadLibpcap();
#endif
