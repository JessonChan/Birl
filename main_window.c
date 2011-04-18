#include <gtk/gtk.h>
#include <string.h>

#include "main_window.h"
#include "set_dialog.h"

GtkWidget *mainWindow;
//设置参数
static void setConfig();

//初始化主窗口
int initMainWindow()
{
    //主窗口
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Birl---Ubuntu锐捷");
    gtk_widget_set_size_request(mainWindow, 400, 280);
    gtk_container_border_width(GTK_CONTAINER(mainWindow),0);
    gtk_window_set_policy(GTK_WINDOW(mainWindow), FALSE, FALSE, TRUE);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(mainWindow), ICO_PATH,NULL);

    //主窗口布局
    GtkWidget *vbox=gtk_vbox_new(FALSE,0);
    GtkWidget *backImage=gtk_image_new_from_file(BACKIMAGE_PATH);
    GtkWidget *inputVbox=gtk_vbox_new(0,0);
    GtkWidget *actionHbox=gtk_hbox_new(0,0);
    GtkWidget *inputPasswdHbox=gtk_hbox_new(0,0);
    GtkWidget *inputUserNameHbox=gtk_hbox_new(0,0);


    gtk_container_add(GTK_CONTAINER(mainWindow),vbox);

    gtk_box_pack_start_defaults(GTK_BOX(vbox),backImage);
    gtk_box_pack_start_defaults(GTK_BOX(vbox),inputVbox);
    gtk_box_pack_start_defaults(GTK_BOX(vbox),actionHbox);


    GtkWidget *userLabel=gtk_label_new("用户名");
    GtkWidget *userEntry =gtk_entry_new();
    gtk_box_pack_start_defaults(GTK_BOX(inputUserNameHbox),userLabel);
    gtk_box_pack_start_defaults(GTK_BOX(inputUserNameHbox),userEntry);



    GtkWidget *passwdLabel=gtk_label_new("密    码");
    GtkWidget *passwdEntry =gtk_entry_new();
    gtk_box_pack_start_defaults(GTK_BOX(inputPasswdHbox),passwdLabel);
    gtk_box_pack_start_defaults(GTK_BOX(inputPasswdHbox),passwdEntry);


    gtk_box_pack_start_defaults(GTK_BOX(inputVbox),inputUserNameHbox);
    gtk_box_pack_start_defaults(GTK_BOX(inputVbox),inputPasswdHbox);

    GtkWidget *loadButton = gtk_button_new_with_label("登录");
    GtkWidget *setConfigButton  = gtk_button_new_with_label("设置");


    gtk_box_pack_start_defaults(GTK_BOX(actionHbox),loadButton);
    gtk_box_pack_start_defaults(GTK_BOX(actionHbox),setConfigButton);


    g_signal_connect(G_OBJECT(mainWindow),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(setConfigButton),"clicked",G_CALLBACK(setConfig),NULL);

    gtk_widget_show_all (mainWindow);

    return TRUE;
}

void setConfig()
{
    debug("main_window.c","setConfig","设置参数对话框");
    initSetDialog(mainWindow);
}
