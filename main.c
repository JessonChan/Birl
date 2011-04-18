#include <stdlib.h>
#include <gtk/gtk.h>

#include "main_window.h"
#include "defines.h"


int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    initMainWindow();
    gtk_main();
    return 0;
}
