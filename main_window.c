#include <gtk/gtk.h>
#include <string.h>

#include "main_window.h"
#include "set_dialog.h"
#include "tray.h"
#include "read_file.h"
#include "main_birl.h"

extern GtkWidget *mainWindow;
GtkWidget *passwdEntry;
GtkWidget *userEntry;
//设置参数
static void setConfig();
static void loading();
//初始化主窗口
int initMainWindow()
{
    gchar version[16]="";
    sprintf(version,"当前版本%s",VERSION);
    debug("main_window.c","initMainWindow",version);
    {
        if(0==readFile())
        {
            debug("main_window.c","initMainWindow","打开配置文件失败，请单击设置进行参数设置");
        }
        else
        {
            debug("main_window.c","initMainWindow","打开配置文件成功");
        }
    }
    //主窗口
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Birl---Ubuntu锐捷");
    gtk_widget_set_size_request(mainWindow, 400, 280);
    gtk_container_border_width(GTK_CONTAINER(mainWindow),0);
    gtk_window_set_policy(GTK_WINDOW(mainWindow), FALSE, FALSE, TRUE);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(mainWindow), ICO_PATH,NULL);

    //主窗口布局
    GtkWidget *layout=gtk_layout_new(0,0);
    GtkWidget *vbox=gtk_vbox_new(0,40);
    GtkWidget *backImage=gtk_image_new_from_file(BACKIMAGE_PATH);
    GtkWidget *inputVbox=gtk_vbox_new(1,22);//均分，间隔10
    GtkWidget *actionHbox=gtk_hbox_new(1,20);
    GtkWidget *inputPasswdHbox=gtk_hbox_new(0,0);//不均分，无间隔
    GtkWidget *inputUserNameHbox=gtk_hbox_new(0,0);

    gtk_widget_set_size_request(layout,400,280);
    gtk_widget_set_size_request(inputVbox,400,60);
    gtk_widget_set_size_request(actionHbox,400,35);
    gtk_widget_set_size_request(inputUserNameHbox,200,35);
    gtk_widget_set_size_request(inputPasswdHbox,200,35);
    gtk_container_add(GTK_CONTAINER(mainWindow),layout);
    gtk_layout_put(GTK_LAYOUT(layout),vbox,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),backImage,0,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),inputVbox,0,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),actionHbox,0,0,0);


    GtkWidget *userLabel=gtk_label_new("\t      用户名");
    userEntry =gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(inputUserNameHbox),userLabel,0,0,0);
    gtk_box_pack_start(GTK_BOX(inputUserNameHbox),userEntry,0,0,0);
    gtk_entry_set_text(GTK_ENTRY(userEntry),user.userName);
    gtk_widget_set_size_request(userLabel,180,25);
    gtk_widget_set_size_request(userEntry,125,25);


    GtkWidget *passwdLabel=gtk_label_new("\t      密    码");
    passwdEntry =gtk_entry_new();
    GtkWidget* saveCheckbutton = gtk_check_button_new_with_label("保存密码");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(saveCheckbutton),TRUE);
    GTK_WIDGET_UNSET_FLAGS(saveCheckbutton, GTK_CAN_FOCUS);
    gtk_box_pack_start(GTK_BOX(inputPasswdHbox),passwdLabel,0,0,0);
    gtk_box_pack_start(GTK_BOX(inputPasswdHbox),passwdEntry,0,0,0);
    gtk_box_pack_start(GTK_BOX(inputPasswdHbox),saveCheckbutton,0,0,8);
    gtk_entry_set_text(GTK_ENTRY(passwdEntry),user.passwd);
    gtk_entry_set_visibility(GTK_ENTRY(passwdEntry), 0);
    gtk_widget_set_size_request(passwdLabel,180,25);
    gtk_widget_set_size_request(passwdEntry,100,25);


    gtk_box_pack_start_defaults(GTK_BOX(inputVbox),inputUserNameHbox);
    gtk_box_pack_start_defaults(GTK_BOX(inputVbox),inputPasswdHbox);

    GtkWidget *loadButton = gtk_button_new_with_label("登录");
    gtk_widget_set_size_request(loadButton, 80, 30);
    GtkWidget *setConfigButton  = gtk_button_new_with_label("设置");
    gtk_widget_set_size_request(setConfigButton, 80, 30);

    gtk_box_pack_start(GTK_BOX(actionHbox),loadButton,0,0,65);
    gtk_box_pack_start(GTK_BOX(actionHbox),setConfigButton,0,0,70);


    g_signal_connect(G_OBJECT(mainWindow),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(setConfigButton),"clicked",G_CALLBACK(setConfig),NULL);
    g_signal_connect(G_OBJECT(loadButton),"clicked",G_CALLBACK(loading),NULL);
    g_signal_connect (GTK_OBJECT(userEntry), "activate",G_CALLBACK(loading),NULL);
    g_signal_connect (GTK_OBJECT(passwdEntry), "activate",G_CALLBACK(loading),NULL);

    gtk_widget_show_all (mainWindow);

    return TRUE;
}

void setConfig()
{
    debug("main_window.c","setConfig","设置参数对话框");
    gtk_widget_hide_all(mainWindow);
    initSetDialog();
}

void loading()
{
    sprintf(user.userName,"%s",gtk_entry_get_text(GTK_ENTRY(userEntry)));
    sprintf(user.passwd,"%s",gtk_entry_get_text(GTK_ENTRY(passwdEntry)));
    if(strlen(user.userName)&&strlen(user.passwd))
    {
        debug("main_window.c","loading","存在密码，登录");
        gtk_widget_hide_all(mainWindow);
        initTray();
        g_thread_create(startBirl,NULL,0,NULL);
    }
    else if(!strlen(user.userName))
    {
        debug("main_window.c","loading","用户名为空，填写");
        gtk_widget_grab_focus(userEntry);
    }
    else if(!strlen(user.passwd))
    {
        debug("main_window.c","loading","密码为空，填写");
        gtk_widget_grab_focus(passwdEntry);
    }
}
