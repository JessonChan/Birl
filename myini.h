/* -*- Mode: C; tab-width: 4; -*- */
/*
* Copyright (C) 2009, HustMoon Studio
*
* 文件名称：myini.h
* 摘	要：读取ini文件+写入ini文件
* 作	者：HustMoon@BYHH
* 修	改：2009.10.8
*/
#ifndef MYINI_H
#define MYINI_H


int loadFile(const char * ,const char * ,char* ,char* ,char *);	/* 读取文件 */
int saveFile(const char *buf, const char *fileName);	/* 写入文件 */

int encodePass(char *dst, const char *osrc);
int decodePass(char *dst, const char *src);

static const unsigned char base64Tab[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
static const char xorRuijie[] = {"~!:?$*<(qw2e5o7i8x12c6m67s98w43d2l45we82q3iuu1z4xle23rt4oxclle34e54u6r8m"};

#endif
