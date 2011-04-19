#include <gtk/gtk.h>

#include "set_dialog.h"
#include "defines.h"

extern GtkWidget *mainWindow;
GtkWidget *dialog;
static void argvConfig();
static void closeSetDialog();

//参数配置窗口
void initSetDialog()
{
    //主窗口
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "设置认证方式");
    gtk_widget_set_size_request(dialog,400, 280);
    gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog),INTERNET_PATH,NULL);

    //布局
    //环境变量设定

    GtkWidget *nicLabel;
    GtkWidget *startModeLabel;
    GtkWidget *dhcpModeLabel;
    GtkWidget *ipLabel;
    GtkWidget *mask_lable;
    GtkWidget *button;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *nicHbox;
    GtkWidget *startModeHbox;
    GtkWidget *dhcpModeHbox;
    GtkWidget *ipHbox;
    GtkWidget *maskHbox;
    GtkWidget *nicComobox;
    GtkWidget *startModeComobox;
    GtkWidget *dhcpModeComobox;
    GtkWidget *ipEntry;
    GtkWidget *maskEntry;
    //设定Label
    nicLabel = gtk_label_new("网    卡:");
    startModeLabel = gtk_label_new("组播方式：");
    dhcpModeLabel= gtk_label_new("DHCP方式:");
    ipLabel = gtk_label_new("静态IP设定:");
    mask_lable = gtk_label_new("静态IP掩码：");


    //设定combo_box
    nicComobox = gtk_combo_box_new_text ();
    startModeComobox = gtk_combo_box_new_text();
    dhcpModeComobox = gtk_combo_box_new_text();
    ipEntry = gtk_entry_new();
    maskEntry=gtk_entry_new();
    gtk_widget_set_size_request(ipEntry, 130, 30);
    gtk_widget_set_size_request(startModeComobox, 130, 30);
    gtk_widget_set_size_request(dhcpModeComobox, 130, 30);
    gtk_widget_set_size_request(nicComobox, 130, 30);
    gtk_widget_set_size_request(maskEntry,130,30);

    // gtk_combo_set_popdown_strings(GTK_COMBO(nicComobox), nicList);
    gtk_combo_box_append_text(GTK_COMBO_BOX(nicComobox),"eth0");
    gtk_combo_box_append_text(GTK_COMBO_BOX(nicComobox),"eth1");
    gchar *sM[2]= {"标准","锐捷"};
    gchar *dM[4]= {"静态","认证前","认证后","二次认证"};
    {
        int i =0;
        for(i=0; i<2; i++)
        {
            gtk_combo_box_append_text(GTK_COMBO_BOX(startModeComobox),sM[i]);
        }
        for(i=0; i<4; i++)
        {
            gtk_combo_box_append_text(GTK_COMBO_BOX(dhcpModeComobox),dM[i]);
        }
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(nicComobox),0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(startModeComobox),0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(dhcpModeComobox),0);

    //  gtk_combo_set_popdown_strings(GTK_COMBO(startModeComobox), startList);
    // gtk_combo_set_popdown_strings(GTK_COMBO(dhcpModeComobox), dhcpList);

//    gtk_entry_set_text(GTK_COMBO(nicComobox)->entry, defaultNic);
//    gtk_entry_set_text(GTK_COMBO(startModeComobox)->entry, defaultStart);
//    gtk_entry_set_text(GTK_COMBO(dhcpModeComobox)->entry, defaultMode);
//   gtk_entry_set_text(ipEntry,defaultIP);
//    gtk_entry_set_text(maskEntry,defaultMask);


    vbox = GTK_DIALOG(dialog)->vbox;
    nicHbox = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nicHbox),nicLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(nicHbox),nicComobox,FALSE,FALSE,0);
    startModeHbox = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(startModeHbox),startModeLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(startModeHbox),startModeComobox,FALSE,FALSE,0);
    dhcpModeHbox = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dhcpModeHbox),dhcpModeLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(dhcpModeHbox),dhcpModeComobox,FALSE,FALSE,0);

    ipHbox=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(ipHbox),ipLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(ipHbox),ipEntry,FALSE,FALSE,0);

    maskHbox=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(maskHbox),mask_lable,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(maskHbox),maskEntry,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(vbox),nicHbox,FALSE,FALSE,7);
    gtk_box_pack_start(GTK_BOX(vbox),startModeHbox,FALSE,FALSE,7);
    gtk_box_pack_start(GTK_BOX(vbox),dhcpModeHbox,FALSE,FALSE,7);

    gtk_box_pack_start(GTK_BOX(vbox),ipHbox,FALSE,FALSE,7);
    gtk_box_pack_start(GTK_BOX(vbox),maskHbox,FALSE,FALSE,7);

    /*向对话框中加入按钮*/
    hbox = GTK_DIALOG(dialog)->action_area;
    button = gtk_button_new_with_label("确定");
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,10);
    g_signal_connect(button, "clicked", G_CALLBACK(argvConfig), NULL);
    g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(closeSetDialog),NULL);
    debug("set_dialog.c","initSetDialog",gtk_combo_box_get_active_text(GTK_COMBO_BOX(nicComobox)));
    gtk_widget_show_all(dialog);
}

void argvConfig()
{
    debug("set_dialog.c","argvCconfig","保存参数");
    gtk_widget_destroy(dialog);
    gtk_widget_show_all(mainWindow);
}
void closeSetDialog()
{
    debug("set_dialog.c","closeSetDialog","未保存参数，关闭设置窗口");
    gtk_widget_destroy(dialog);
    gtk_widget_show_all(mainWindow);
}
