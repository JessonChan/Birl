/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）木瓜无衣 （1401570404@qq.com)

*/



#include "common.h"
#include "config.h"
#include "mentohust.h"
#include "trayicon.h"
#include "gtk/gtk.h"

int main (int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    main_window_init();
    trayIcon_init();
    gtk_main();
    return 0;
}
