#include <uiRGB.h>
#include <imgRGB.h>
#include <uiMain.h>

void set_img_to_pixbuf_rgb(ImageRGB *imgRGB, GdkPixbuf *pixbuf)
{
  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

  for (int i = 0; i < imgRGB->dim.altura; i++)
  {
    for (int j = 0; j < imgRGB->dim.largura; j++)
    {
      int index = (i * imgRGB->dim.largura + j) * 3; 
      pixels[index] = imgRGB->pixels[i * imgRGB->dim.largura + j].red;
      pixels[index + 1] = imgRGB->pixels[i * imgRGB->dim.largura + j].green;
      pixels[index + 2] = imgRGB->pixels[i * imgRGB->dim.largura + j].blue;
    }
  }
}

void on_flip_horizontal_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void) widget;
  (void) data;
  
  // imgRGB = flip_horizontal_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(imgRGB, pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}

void on_flip_vertical_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void) widget;
  (void) data;

  // imgRGB = flip_vertical_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(imgRGB, pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}
