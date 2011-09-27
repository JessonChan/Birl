/*

Birl is Ruijie Linux

作者：木瓜无衣：（1401570404@qq.com)
*/



#ifndef COMMON_H
#define COMMON_H

#include "gtk/gtk.h"
#include "trayicon.h"
#include "types.h"

#include <pthread.h>
#include "mentohust.h"
#include "trayicon.h"
#include "config.h"
#include "types.h"
#include "dlfunc.h"
#include "myini.h"
#include <string.h>

extern GtkWidget *main_window;
GdkPixbuf *create_pixbuf(const gchar *filename);
gboolean connect_login();
void connect_logoff();
void connect_exit();
void showMesg();
void set_config();
//环境变量设定
void argv_config();
GtkWidget *dialog;
GtkWidget* frame ;
GtkWidget *nic_label;
GtkWidget *startMode_label;
GtkWidget *dhcpMode_label;
//GtkWidget *ip_label;
//GtkWidget *mask_lable;
GtkWidget *button;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *nic_hbox;
GtkWidget *startMode_hbox;
GtkWidget *dhcpMode_hbox;
//GtkWidget *ip_hbox;
//GtkWidget *mask_hbox;
GtkWidget *nic_comobox;
GtkWidget *startMode_comobox;
GtkWidget *dhcpMode_comobox;
GtkWidget *ip_entry;
GtkWidget *mask_entry;
GList *nicList;
GList *startList;
GList *dhcpList ;


ARGV argv;


#endif // COMMON_H_INCLUDED
