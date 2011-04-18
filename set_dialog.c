#include <gtk/gtk.h>

#include "set_dialog.h"
#include "defines.h"

//参数配置窗口
void initSetDialog()
{
    GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "设置认证方式");
    gtk_widget_set_size_request(GTK_WINDOW(dialog),400, 280);
    gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog),INTERNET_PATH,NULL);

    gtk_widget_show_all(dialog);
}


