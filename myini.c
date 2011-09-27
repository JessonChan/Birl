/* -*- Mode: C; tab-width: 4; -*- */
/*
* Copyright (C) 2009, HustMoon Studio
*
* 文件名称：myini.c
* 摘	要：读取ini文件+写入ini文件
* 作	者：HustMoon@BYHH
* 修	改：2009.10.8
*/
#include "myini.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int loadFile(const char * u,const char * p,char * n,char *s,char* d)
{
    FILE *fp = NULL;
    char tmp[32];
    if ((fp=fopen(CFG_FILE, "r")) == NULL)
        return 0;
    fgets(tmp,255,fp);//这是第一行的[birl]
    fscanf(fp,"%s",u);
    fscanf(fp,"%s",tmp);;//密码
    decodePass(p,tmp);
    fscanf(fp,"%s",n);//网hhu
    fscanf(fp,"%s",tmp);//startmode
    strcpy(s,strcmp(tmp,"Standerd")==0?"标准":"锐捷");
    fscanf(fp,"%s",tmp);//dhcpmode
    strcpy(d,strcmp(tmp,"None")==0?"无":strcmp(tmp,"Double")==0?"二次认证":strcmp(tmp,"Before")==0?"认证前":"认证后");
//   printf("%s,%s,%s,%s,%s\n",u,p,n,s,d);
    fclose(fp);
    return 1;
}


int saveFile(const char *buf, const char *fileName)
{
    FILE *fp;
    int result;

    if ((fp=fopen(fileName, "w")) == NULL)
        return -1;
    //result = fwrite(buf, strlen(buf), 1, fp)<1 ? -1 : 0;
    result = fprintf(fp,"%s",buf);
    fclose(fp);
    return result;
}
int encodePass(char *dst, const char *osrc)
{
    unsigned char in[3], buf[70];
    unsigned char *src = buf;
    int sz = strlen(osrc);
    int i, len;
    if (sizeof(xorRuijie) < sz)
        return -1;
    for(i=0; i<sz; i++)
        src[i] = osrc[i] ^ xorRuijie[i];
    while (sz > 0)
    {
        for (len=0, i=0; i<3; i++, sz--)
        {
            if (sz > 0)
            {
                len++;
                in[i] = src[i];
            }
            else in[i] = 0;
        }
        src += 3;
        if (len)
        {
            dst[0] = base64Tab[ in[0] >> 2 ];
            dst[1] = base64Tab[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
            dst[2] = len > 1 ? base64Tab[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=';
            dst[3] = len > 2 ? base64Tab[ in[2] & 0x3f ] : '=';
            dst += 4;
        }
    }
    *dst = '\0';
    return 0;
}

int decodePass(char *dst, const char *src)
{
    unsigned esi = 0, idx = 0;
    int i=0, j=0, equal=0;
    for(; src[i]!='\0'; i++)
    {
        if (src[i] == '=')
        {
            if (++equal > 2)
                return -1;
        }
        else
        {
            for(idx=0; base64Tab[idx]!='\0'; idx++)
            {
                if(base64Tab[idx] == src[i])
                    break;
            }
            if (idx == 64)
                return -1;
            esi += idx;
        }
        if(i%4 == 3)
        {
            dst[j++] = (char)(esi>>16);
            if(equal < 2)
                dst[j++] = (char)(esi>>8);
            if(equal < 1)
                dst[j++] = (char)esi;
            esi = 0;
            equal = 0;
        }
        esi <<= 6;
    }
    if (i%4!=0 || sizeof(xorRuijie)<j)
        return -1;
    for(i=0; i<j; i++)
        dst[i] ^= xorRuijie[i];
    dst[j] = '\0';
    return 0;
}
