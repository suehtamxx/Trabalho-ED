#include <uiRGB.h>
#include <imgRGB.h>
#include <uiMain.h>
#include <gtk/gtk.h>

GtkWidget *imageWidgetRGB;

void setup_ui_rgb(GtkWidget *stack)
{
  // RGB Image Handling
  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), mainBox, "Manipulação RGB", "Manipulação RGB");

  // GdkPixbuf *pixbufRGB = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  // set_img_to_pixbuf_rgb(imgRGB, pixbufRGB);

  // imageWidgetRGB = gtk_image_new_from_pixbuf(pixbufRGB);
  // gtk_box_pack_start(GTK_BOX(mainBox), imageWidgetRGB, TRUE, TRUE, 0);

  // // butons for manipulation
  // GtkWidget *buttonFlip = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
  // gtk_box_pack_start(GTK_BOX(mainBox), buttonFlip, FALSE, FALSE, 2);

  // GtkWidget *flipHorizontalButtonRGB = gtk_toggle_button_new_with_label("Flip Horizontal");
  // g_signal_connect(flipHorizontalButtonRGB, "toggled", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonFlip), flipHorizontalButtonRGB, TRUE, TRUE, 0);

  // GtkWidget *flipVerticalButtonRGB = gtk_toggle_button_new_with_label("Flip Vertical");
  // g_signal_connect(flipVerticalButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonFlip), flipVerticalButtonRGB, TRUE, TRUE, 0);

  // GtkWidget *transposeButtonRGB = gtk_toggle_button_new_with_label("Transpose");
  // g_signal_connect(transposeButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonFlip), transposeButtonRGB, TRUE, TRUE, 0);

  // // buttons for rotation
  // GtkWidget *buttonRotation = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
  // gtk_box_pack_start(GTK_BOX(mainBox), buttonRotation, FALSE, FALSE, 2);

  // GtkWidget *rotate90ButtonRGB = gtk_button_new_with_label("Rotate 90º");
  // g_signal_connect(rotate90ButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonRotation), rotate90ButtonRGB, TRUE, TRUE, 0);

  // GtkWidget *rotate180ButtonRGB = gtk_button_new_with_label("Rotate -90º");
  // g_signal_connect(rotate180ButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonRotation), rotate180ButtonRGB, TRUE, TRUE, 0);

  // // filters
  // GtkWidget *buttonFilters = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  // gtk_box_pack_start(GTK_BOX(mainBox), buttonFilters, FALSE, FALSE, 2);

  // GtkWidget *claheButtonRGB = gtk_toggle_button_new_with_label("filtro CLAHE");
  // g_signal_connect(claheButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonFilters), claheButtonRGB, TRUE, TRUE, 0);

  // GtkWidget *medianBlurButtonRGB = gtk_toggle_button_new_with_label("filtro Median Blur");
  // g_signal_connect(medianBlurButtonRGB, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonFilters), medianBlurButtonRGB, TRUE, TRUE, 0);

  // // Gerar uma linha
  // GtkWidget *line = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  // gtk_box_pack_start(GTK_BOX(mainBox), line, FALSE, FALSE, 2);

  // // Butão para imagem aleatória
  // GtkWidget *randomButton = gtk_button_new_with_label("---Imagem Aleatória---");
  // g_signal_connect(randomButton, "clicked", G_CALLBACK(NULL), NULL);
  // gtk_box_pack_start(GTK_BOX(mainBox), randomButton, FALSE, FALSE, 2);

  // int button_width = 200;
  // gtk_widget_set_size_request(flipHorizontalButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(flipVerticalButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(transposeButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(rotate90ButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(rotate180ButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(claheButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(medianBlurButtonRGB, button_width, -1);
  // gtk_widget_set_size_request(randomButton, button_width, -1);
}

static void set_img_to_pixbuf_rgb(ImageRGB *imgRGB, GdkPixbuf *pixbuf)
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

static void on_flip_horizontal_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  // imgRGB = flip_horizontal_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(imgRGB, pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}

static void on_flip_vertical_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  // imgRGB = flip_vertical_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(imgRGB, pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}
