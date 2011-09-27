/*
Birl is Ruijie Linux

作者：木瓜无衣 （1401570404@qq.com)

*/



#ifndef CONFIG_H
#define CONFIG_H

#include <gtk/gtk.h>
#include "common.h"

GtkWidget *main_window;
GtkWidget *main_frame;
GtkWidget *login_button;
GtkWidget *set_button;
GtkWidget *username_label;
GtkWidget *password_label;
GtkWidget *username_comobox;
GtkWidget *password_entry;
GtkWidget *main_window_backimage;
GtkWidget *save_checkbutton;
GList *items_username_comobox;

gchar guiUsername[16];
gchar guiPassword[16];
gchar defaultNic[16];
gchar defaultStart[16];
gchar defaultMode[16];
//gchar defaultIP[16];
//gchar defaultMask[16];
int nicNum;
int getNicMsg();
CSTRING nicMsg;

GtkWidget *connect_frame;
GtkWidget *connect_label;
GtkWidget *connect_exit_button;


static int config_button_is_clicked;

void main_window_init();
void set_focus();

#endif // CONFIG_H_INCLUDED
