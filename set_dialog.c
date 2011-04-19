#include <gtk/gtk.h>

#include "set_dialog.h"
#include "defines.h"

extern GtkWidget *mainWindow;
GtkWidget *dialog;
static void argvConfig();

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
    GList *nicList;
    GList *startList;
    GList *dhcpList ;
    //设定Label
    nicLabel = gtk_label_new("网    卡:");
    startModeLabel = gtk_label_new("组播方式：");
    dhcpModeLabel= gtk_label_new("DHCP方式:");
    ipLabel = gtk_label_new("静态IP设定:");
    mask_lable = gtk_label_new("静态IP掩码：");


    //设定combo_box
    nicComobox = gtk_combo_new();
    startModeComobox = gtk_combo_new();
    dhcpModeComobox = gtk_combo_new();
    ipEntry = gtk_entry_new();
    maskEntry=gtk_entry_new();
    gtk_widget_set_size_request(ipEntry, 130, 30);
    gtk_widget_set_size_request(startModeComobox, 130, 30);
    gtk_widget_set_size_request(dhcpModeComobox, 130, 30);
    gtk_widget_set_size_request(nicComobox, 130, 30);
    gtk_widget_set_size_request(maskEntry,130,30);

    //设定combo_box的Glist
    nicList=NULL;
    nicList= g_list_append(nicList,"eth0");
    startList = NULL;
    dhcpList = NULL;
    gchar* sM1="标准";
    gchar* sM2="锐捷";
    startList = g_list_append(startList,sM1);
    startList = g_list_append(startList,sM2);

    gchar* dM1="静态";
    gchar* dM2="二次认证";
    gchar* dM3="认证前";
    gchar* dM4="认证后";

    dhcpList = g_list_append(dhcpList,dM1);
    dhcpList = g_list_append(dhcpList,dM2);
    dhcpList = g_list_append(dhcpList,dM3);
    dhcpList = g_list_append(dhcpList,dM4);

    gtk_combo_set_popdown_strings(GTK_COMBO(nicComobox), nicList);
    gtk_combo_set_popdown_strings(GTK_COMBO(startModeComobox), startList);
    gtk_combo_set_popdown_strings(GTK_COMBO(dhcpModeComobox), dhcpList);

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
    gtk_widget_show_all(dialog);
}

void argvConfig()
{
    debug("set_dialog.c","argvCconfig","保存参数");
    //gchar *n=gtk_entry_get_text(gtk_entry(GTK_COMBO(nicComobox)->entry));
//    gchar *s= gtk_entry_get_text(gtk_entry(GTK_COMBO(startModeComobox)->entry));
//    gchar *d = gtk_entry_get_text(gtk_entry(GTK_COMBO(dhcpModeComobox)->entry));
//    gchar *i = gtk_entry_get_text(ipEntry);
//    gchar *m=gtk_entry_get_text(maskEntry);

   // sprintf(user.nic,"%s",n);
    //debug("set_dialog.c","argvConfig",user.nic)
//    sprintf(user.startMode,"%s",s);
//    sprintf(user.dhcpMode,"%s",d);
//    sprintf(user.ip,"%s",i);
//    sprintf(user.mask,"%s",m);
    gtk_widget_destroy(dialog);
    gtk_widget_show_all(mainWindow);
}
