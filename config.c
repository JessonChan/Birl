/*
Birl is Ruijie Linux

作者：木瓜无衣 （1401570404@qq.com)

*/



#include "config.h"
#include "types.h"
#include "dlfunc.h"
#include "myini.h"

#define USERNAME_SIZE 65
#define PASSWORD_SIZE 64

void getString(char **p,char **q,char *m)
{
    while(**q!='\n')
        (*q)++;
    **q='\0';
    strcpy(m,*p);
    (*q)++;
    *p=*q;
}
void main_window_init()
{

    printf("当前版本%s;",VERSION);
    if (load_libpcap() == -1)
    {
        showWarningMesg("老大，你有没有用sudo 吧！！！！打不开libpcap？");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(0==(nicNum=getNicMsg(nicMsg)))
        {
            showWarningMesg("我打不开网卡呀，你没有以超级身份运行我吧！！！！");
            exit(EXIT_FAILURE);
        }
    }
    {
        int  fileRead=loadFile(guiUsername,guiPassword,defaultNic,defaultStart,defaultMode);
        if(0==fileRead)
        {
            printf("配置文件读取失败，采用默认方式");
            strcpy(defaultNic,"eth0");
            strcpy(defaultStart,"锐捷");
            strcpy(defaultMode,"二次认证");
        }
        else if(1==fileRead)
        {
            printf("成功读取配置文件\n");
            //printf("当前版本%s",VERSION);
        }
    }
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Birl---Ubuntu锐捷");
    gtk_widget_set_size_request(GTK_WINDOW(main_window), 400, 280);
    gtk_window_set_policy(GTK_WINDOW(main_window), FALSE, FALSE, TRUE);
    gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon(GTK_WINDOW(main_window), create_pixbuf(ICO_PATH));

    main_frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_window), main_frame);

    main_window_backimage = gtk_image_new_from_file(BACKIMAGE_PATH);
    gtk_fixed_put(GTK_WINDOW(main_frame), main_window_backimage, 0, 0);

    login_button = gtk_button_new_with_label("登 录");
    gtk_widget_set_size_request(login_button, 70, 30);
    gtk_fixed_put(GTK_FIXED(main_frame), login_button, 80, 220);

    set_button = gtk_button_new_with_label("设 置");
    gtk_widget_set_size_request(set_button, 70, 30);
    gtk_fixed_put(GTK_FIXED(main_frame), set_button, 250, 220);

    username_label = gtk_label_new("用户名");
    gtk_fixed_put(GTK_FIXED(main_frame), username_label, 100, 115);

    password_label = gtk_label_new("密   码");
    gtk_fixed_put(GTK_FIXED(main_frame), password_label, 100, 165);


    username_comobox = gtk_combo_new();
    gtk_widget_set_size_request(username_comobox, 130, 30);
    gtk_fixed_put(GTK_FIXED(main_frame), username_comobox, 170, 110);
    GList *usernamelist = NULL;
    usernamelist = g_list_append(usernamelist, guiUsername);
    gtk_combo_set_popdown_strings(GTK_COMBO(username_comobox), usernamelist);


    password_entry = gtk_entry_new();
    gtk_widget_set_size_request(password_entry, 100, 30);
    gtk_fixed_put(GTK_FIXED(main_frame), password_entry, 170, 160);

    gtk_signal_connect (GTK_OBJECT(password_entry), "activate",
                        GTK_SIGNAL_FUNC(connect_login),
                        NULL);
    gtk_combo_disable_activate(username_comobox);
    gtk_signal_connect (GTK_OBJECT(GTK_COMBO (username_comobox)->entry), "activate",
                        GTK_SIGNAL_FUNC(set_focus),
                        NULL );
    save_checkbutton = gtk_check_button_new_with_label("保存密码");
    gtk_fixed_put(GTK_FIXED(main_frame), save_checkbutton, 275, 165);
    gtk_toggle_button_set_active(save_checkbutton,TRUE);
    GTK_WIDGET_UNSET_FLAGS(save_checkbutton, GTK_CAN_FOCUS);


    gtk_entry_set_text(password_entry, guiPassword);
    gtk_entry_set_visibility(password_entry, FALSE);

    gtk_widget_show_all(main_window);
    g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(set_button, "clicked", G_CALLBACK(set_config), NULL);
    g_signal_connect(login_button, "clicked", G_CALLBACK(connect_login), NULL);
}

void set_focus()
{
    gtk_widget_grab_focus(password_entry);
}


void showWarningMesg(char * msg)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,             //跟随父窗口关闭
                                    GTK_MESSAGE_INFO,                        //显示图标
                                    GTK_BUTTONS_OK,                             //不显示按钮
                                    msg);
    GtkWidget *image = gtk_image_new_from_file(DATA_INSTALL_DIR"/birl/birl.ico");
    gtk_widget_show(image);
    gtk_message_dialog_set_image (dialog, image);
    gtk_window_set_title(GTK_WINDOW(dialog), ("Birl提示："));//对话框的标题
    gtk_dialog_run(GTK_DIALOG(dialog));//运行对话框
    gtk_widget_destroy(dialog);//删除对话框
}




int  getNicMsg(CSTRING nicMsg)
{
    pcap_if_t *alldevs, *d;
    int nicNum =0;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, errbuf)==-1 || alldevs==NULL)
    {
        /*查找网卡失败*/
        nicNum = 0;
    }
    for (d=alldevs; d!=NULL; d=d->next)
        if (!(d->flags & PCAP_IF_LOOPBACK) && strcmp(d->name, "any")!=0)
        {
            //sprintf(nicMsg[nicNum],"%s\0",d->name);
            strcpy(nicMsg[nicNum],d->name);
            strcat(nicMsg[nicNum],"\0");
            nicNum++;
        }
    return nicNum;
}
