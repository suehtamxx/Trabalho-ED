#pragma once

#include <gtk/gtk.h>
#include <imgStruct.h>

void setup_ui_rgb(GtkWidget *stack);
void set_img_to_pixbuf_rgb(ImageRGB *imgRGB, GdkPixbuf *pixbuf);
void on_flip_horizontal_rgb_button_clicked(GtkWidget *widget, gpointer data);
void on_flip_vertical_rgb_button_clicked(GtkWidget *widget, gpointer data);
