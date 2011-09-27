/*
Birl is Ruijie Linux

作者：JessonChan（chinachendongpo@gmail.com//OR//i@moreblue.cn）木瓜无衣 （1401570404@qq.com)

*/

#include "about.h"
#include "trayicon.h"

void trayIconPopup(GtkStatusIcon *status_icon, guint button, guint32 active_time, gpointer popUpMenu)
{
    gtk_menu_popup(GTK_MENU(popUpMenu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, active_time);
}
void trayIcon_init()
{
    trayicon = gtk_status_icon_new_from_file(ICO_PATH);
    trayicon_menu = gtk_menu_new();
    //trayicon_menuitem_logoff = gtk_menu_item_new_with_label("断开链接");
    trayicon_menuitem_exit = gtk_menu_item_new_with_label("退出");
    trayicon_menuitem_severMsg = gtk_menu_item_new_with_label("服务器消息");
    // trayicon_menuitem_about=gtk_menu_item_new_with_label("关于");

    g_signal_connect(G_OBJECT(trayicon_menuitem_exit), "activate", G_CALLBACK(connect_exit), NULL);
    // g_signal_connect(G_OBJECT(trayicon_menuitem_logoff), "activate", G_CALLBACK(connect_logoff), NULL);
    g_signal_connect(G_OBJECT(trayicon_menuitem_severMsg), "activate", G_CALLBACK(showMesg), NULL);
    //  g_signal_connect(G_OBJECT(trayicon_menuitem_about),"activeate",G_CALLBACK(showMesg),NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu), trayicon_menuitem_exit);
    //  gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu), trayicon_menuitem_logoff);
    gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu), trayicon_menuitem_severMsg);
    //  gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu),trayicon_menuitem_about);
    gtk_widget_show_all(trayicon_menu);
    gtk_status_icon_set_tooltip (trayicon, "Birl");
    gtk_status_icon_set_visible(trayicon, FALSE);
    g_signal_connect(GTK_STATUS_ICON (trayicon), "activate", GTK_SIGNAL_FUNC (about), NULL);
    g_signal_connect(GTK_STATUS_ICON (trayicon), "popup-menu", GTK_SIGNAL_FUNC (trayIconPopup), trayicon_menu);

}

void trayIcon_destroy()
{
    gtk_widget_destroy(trayicon_menu);
}
