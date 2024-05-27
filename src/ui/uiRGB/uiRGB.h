#pragma once

#include <gtk/gtk.h>
#include <imgStruct.h>

extern GtkWidget *imageWidgetRGB;

void setup_ui_rgb(GtkWidget *stack);
static void set_img_to_pixbuf_rgb(ImageRGB *imgRGB, GdkPixbuf *pixbuf);
