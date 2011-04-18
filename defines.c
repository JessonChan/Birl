#include <stdio.h>

#include "defines.h"

//调试信息输出
void debug(const char *fileName,const char *functionName,const char *debugInfo)
{
    printf("Debug\t%s    文件：%s    函数：%s\n",debugInfo,fileName,functionName);
}


