#include "about.h"

#include <gtk/gtk.h>
#include "defines.h"

void about()
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(ABOUT_ICO, NULL);

    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Birl");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), VERSION);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),
                                   "(c) JessonChan");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
                                  "Birl is a simple GUI Ruijie client for Ubuntu.\nBirl Is Ruijie for Linux.");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),
                                 "http://www.cnblogs.com/JessonChan/");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}
