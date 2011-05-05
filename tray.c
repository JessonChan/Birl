#include "tray.h"
#include "defines.h"
#include "about.h"

extern GtkWidget* mainWindow;
extern gchar tipMsg[64];
extern GtkStatusIcon* trayicon ;
static void trayIconPopup(GtkStatusIcon *status_icon, guint button, guint32 active_time, gpointer popUpMenu)
{
    gtk_menu_popup(GTK_MENU(popUpMenu), NULL, NULL, gtk_status_icon_position_menu, status_icon, button, active_time);
}
static void loadout()
{
    gtk_main_quit();
}
static void showSeverMsg()
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,             //跟随父窗口关闭
                                    GTK_MESSAGE_INFO,                        //显示图标
                                    GTK_BUTTONS_OK,                             //不显示按钮
                                    "SeverMsg");
    GtkWidget *image = gtk_image_new_from_file(ICO_PATH);
    gtk_widget_show(image);
    gtk_message_dialog_set_image (GTK_MESSAGE_DIALOG(dialog), image);
    gtk_window_set_title(GTK_WINDOW(dialog), ("Birl提示："));//对话框的标题
    gtk_dialog_run(GTK_DIALOG(dialog));//运行对话框
    gtk_widget_destroy(dialog);//删除对话框
}
//初始化托盘图标
void initTray()
{
    trayicon = gtk_status_icon_new_from_file(ICO_PATH);
    GtkWidget* trayiconMenu = gtk_menu_new();
    GtkWidget* menuItemExit = gtk_menu_item_new_with_label("退出");
    GtkWidget* menuItemAbout = gtk_menu_item_new_with_label("关于");
    GtkWidget* menuItemSeverMsg = gtk_menu_item_new_with_label("服务器消息");

    gtk_menu_shell_append(GTK_MENU_SHELL(trayiconMenu), menuItemExit);
    gtk_menu_shell_append(GTK_MENU_SHELL(trayiconMenu),menuItemAbout);
    gtk_menu_shell_append(GTK_MENU_SHELL(trayiconMenu), menuItemSeverMsg);

    gtk_widget_show_all(trayiconMenu);
    gchar tipMsg[16];
    sprintf(tipMsg,"%s  %s","Birl",VERSION);
    gtk_status_icon_set_tooltip (trayicon, tipMsg);
    gtk_status_icon_set_visible(trayicon, 1);
    g_signal_connect(GTK_STATUS_ICON (trayicon), "popup-menu", GTK_SIGNAL_FUNC (trayIconPopup), trayiconMenu);
    g_signal_connect(GTK_OBJECT(menuItemExit),"activate",G_CALLBACK(loadout),NULL);
    g_signal_connect(GTK_OBJECT(menuItemAbout),"activate",G_CALLBACK(about),NULL);
    g_signal_connect(GTK_OBJECT(menuItemSeverMsg),"activate",G_CALLBACK(showSeverMsg),NULL);
}
