

#include "tray.h"
#include "defines.h"

//初始化托盘图标
void initTray()
{
    GtkStatusIcon* trayicon = gtk_status_icon_new_from_file(ICO_PATH);
    GtkWidget* trayiconMenu = gtk_menu_new();
    GtkWidget* menuItemExit = gtk_menu_item_new_with_label("退出");
    GtkWidget* menuItemSeverMsg = gtk_menu_item_new_with_label("服务器消息");

    gtk_menu_shell_append(GTK_MENU_SHELL(trayiconMenu), menuItemExit);

    gtk_menu_shell_append(GTK_MENU_SHELL(trayiconMenu), menuItemSeverMsg);

    gtk_widget_show_all(trayiconMenu);
    gtk_status_icon_set_tooltip (trayicon, VERSION);
    gtk_status_icon_set_visible(trayicon, 1);
}
