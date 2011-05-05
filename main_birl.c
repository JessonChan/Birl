
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "main_birl.h"

extern GtkStatusIcon* trayicon ;
extern USER user;
extern NET net;

gpointer startBirl()
{
    user2net();
    return (gpointer)NULL;
}
