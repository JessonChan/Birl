

#include "tray.h"
#include "defines.h"

//初始化托盘图标
void initTray()
{
    GtkStatusIcon* trayicon = gtk_status_icon_new_from_file(ICO_PATH);
    GtkWidget* trayicon_menu = gtk_menu_new();
    GtkWidget* trayicon_menuitem_exit = gtk_menu_item_new_with_label("退出");
    GtkWidget* trayicon_menuitem_severMsg = gtk_menu_item_new_with_label("服务器消息");

    gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu), trayicon_menuitem_exit);

    gtk_menu_shell_append(GTK_MENU_SHELL(trayicon_menu), trayicon_menuitem_severMsg);

    gtk_widget_show_all(trayicon_menu);
    gtk_status_icon_set_tooltip (trayicon, VERSION);
    gtk_status_icon_set_visible(trayicon, 1);

}
