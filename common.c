/*
Birl is Ruijie Linux

作者：木瓜无衣：（1401570404@qq.com)

*/



#include "common.h"

extern char ruijieMsg[1024];
GdkPixbuf *create_pixbuf(const gchar *filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf)
    {
        g_error_free(error);
    }

    return pixbuf;
}

gboolean connect_login()
{
    gtk_widget_hide_all(main_window);
    //  gtk_status_icon_set_visible(trayicon,TRUE);
    const gchar* tU = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(username_comobox)->entry));
    const gchar* tP = gtk_entry_get_text(GTK_ENTRY(password_entry));
    printf("隐藏所有的窗口,开始链接 采用的方式：%s,%s,%s\n",defaultNic,defaultStart,defaultMode);
    sprintf(argv[0],"%s",defaultNic);
    sprintf(argv[1],"%s",defaultStart);
    sprintf(argv[2],"%s",defaultMode);
    printf("隐藏所有的窗口,开始链接 采用的方式：%s,%s,%s\n",argv[0],argv[1],argv[2]);
    startConnect(tU,tP,argv);
    if(statasConnect() == 1)
    {
        printf("认证成功!!");
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(save_checkbutton)))
        {
            char cofig[100]="";
            char encodePasswd[16];
            sprintf(cofig,"%s\n","[Birl]");
            strcat(cofig,tU);
            strcat(cofig,"\n");
            encodePass(encodePasswd,tP);
            strcat(cofig,encodePasswd);
            strcat(cofig,"\n");
            strcat(cofig,argv[0]);
            strcat(cofig,"\n");
            strcat(cofig,strcmp(argv[1],"标准")==0?"Standard":"Ruijie");
            strcat(cofig,"\n");
            strcat(cofig,strcmp(argv[2],"无")==0?"None":strcmp(argv[2],"二次认证")==0?"Double":strcmp(argv[2],"认证前")==0?"Before":"After");
            strcat(cofig,"\n");
            saveFile(cofig,CFG_FILE);
        }
        gtk_status_icon_set_visible(trayicon,TRUE);
        printf("显示托盘，并把保持在线的线程进行下去。\n");
        g_thread_create(keepConnect, NULL, FALSE, NULL);
    }
    else
    {
        printf("认证失败了！！");
        showMesg();
        return FALSE;
    }
    printf("登陆完成，上网状态");
    return TRUE;
}

//断开功能没有完善
void connect_logoff()
{
    endConnect();
    gdk_threads_leave();
    gtk_widget_show_all(main_window);
}

void connect_exit()
{
    // endConnect();
    gdk_threads_leave();
    gtk_main_quit();
}

void showMesg()
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,             //跟随父窗口关闭
                                    GTK_MESSAGE_INFO,                        //显示图标
                                    GTK_BUTTONS_OK,                             //不显示按钮
                                    ruijieMsg);
    GtkWidget *image = gtk_image_new_from_file(DATA_INSTALL_DIR"/birl/birl.ico");
    gtk_widget_show(image);
    gtk_message_dialog_set_image (GTK_MESSAGE_DIALOG(dialog), image);
    gtk_window_set_title(GTK_WINDOW(dialog), ("Birl提示："));//对话框的标题
    gtk_dialog_run(GTK_DIALOG(dialog));//运行对话框
    gtk_widget_destroy(dialog);//删除对话框
}

void set_config()
{
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "设置认证方式");
    gtk_widget_set_size_request(GTK_WINDOW(dialog), 360, 280);
    gtk_window_set_icon(GTK_WINDOW(dialog), create_pixbuf(INTERNET_PATH));
    gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);


    //设定Label
    nic_label = gtk_label_new("网    卡:");
    startMode_label = gtk_label_new("组播方式：");
    dhcpMode_label= gtk_label_new("DHCP方式:");
    //ip_label = gtk_label_new("静态IP设定:");
    // mask_lable = gtk_label_new("静态IP掩码：");


    //设定combo_box
    nic_comobox = gtk_combo_new();
    startMode_comobox = gtk_combo_new();
    dhcpMode_comobox = gtk_combo_new();
    //ip_entry = gtk_entry_new();
    //mask_entry=gtk_entry_new();
    //gtk_widget_set_size_request(ip_entry, 130, 30);
    gtk_widget_set_size_request(startMode_comobox, 130, 30);
    gtk_widget_set_size_request(dhcpMode_comobox, 130, 30);
    gtk_widget_set_size_request(nic_comobox, 130, 30);
    // gtk_widget_set_size_request(mask_entry,130,30);

    //设定combo_box的Glist
    nicList = NULL;
    {
        int i =0;
        while(i<nicNum)
        {
            nicList=g_list_append(nicList,nicMsg[i]);
            i++;
        }
    }

    startList = NULL;
    dhcpList = NULL;
    gchar* sM1="标准";
    gchar* sM2="锐捷";
    startList = g_list_append(startList,sM1);
    startList = g_list_append(startList,sM2);

    gchar* dM1="无";
    gchar* dM2="二次认证";
    gchar* dM3="认证前";
    gchar* dM4="认证后";

    dhcpList = g_list_append(dhcpList,dM1);
    dhcpList = g_list_append(dhcpList,dM2);
    dhcpList = g_list_append(dhcpList,dM3);
    dhcpList = g_list_append(dhcpList,dM4);

    gtk_combo_set_popdown_strings(GTK_COMBO(nic_comobox), nicList);
    gtk_combo_set_popdown_strings(GTK_COMBO(startMode_comobox), startList);
    gtk_combo_set_popdown_strings(GTK_COMBO(dhcpMode_comobox), dhcpList);

    gtk_entry_set_text(GTK_COMBO(nic_comobox)->entry, defaultNic);
    gtk_entry_set_text(GTK_COMBO(startMode_comobox)->entry, defaultStart);
    gtk_entry_set_text(GTK_COMBO(dhcpMode_comobox)->entry, defaultMode);
//    gtk_entry_set_text(ip_entry,defaultIP);
//    gtk_entry_set_text(mask_entry,defaultMask);


    vbox = GTK_DIALOG(dialog)->vbox;
    nic_hbox = gtk_hbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(nic_hbox),nic_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(nic_hbox),nic_comobox,FALSE,FALSE,0);
    startMode_hbox = gtk_hbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(startMode_hbox),startMode_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(startMode_hbox),startMode_comobox,FALSE,FALSE,0);
    dhcpMode_hbox = gtk_hbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(dhcpMode_hbox),dhcpMode_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(dhcpMode_hbox),dhcpMode_comobox,FALSE,FALSE,0);
//    ip_hbox=gtk_hbox_new(TRUE,5);
//    gtk_box_pack_start(GTK_BOX(ip_hbox),ip_label,FALSE,FALSE,0);
//    gtk_box_pack_start(GTK_BOX(ip_hbox),ip_entry,FALSE,FALSE,0);
//    mask_hbox=gtk_hbox_new(TRUE,5);
//    gtk_box_pack_start(GTK_BOX(mask_hbox),mask_lable,FALSE,FALSE,0);
//    gtk_box_pack_start(GTK_BOX(mask_hbox),mask_entry,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(vbox),nic_hbox,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),startMode_hbox,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),dhcpMode_hbox,FALSE,FALSE,10);
    // gtk_box_pack_start(GTK_BOX(vbox),ip_hbox,FALSE,FALSE,10);
    // gtk_box_pack_start(GTK_BOX(vbox),mask_hbox,FALSE,FALSE,10);

    /*向对话框中加入按钮*/
    hbox = GTK_DIALOG(dialog)->action_area;
    button = gtk_button_new_with_label("确定");
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
    g_signal_connect(button, "clicked", G_CALLBACK(argv_config), NULL);

    gtk_widget_show_all(dialog);
}

void argv_config()
{

    config_button_is_clicked=1;
    gchar *n=gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(nic_comobox)->entry));
    gchar *s= gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(startMode_comobox)->entry));
    gchar *d = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(dhcpMode_comobox)->entry));

    sprintf(defaultNic,"%s",n);
    sprintf(defaultStart,"%s",s);
    sprintf(defaultMode,"%s",d);
    gtk_widget_destroy(dialog);
}

