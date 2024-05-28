#include <uiRGB.h>
#include <imgRGB.h>
#include <uiMain.h>
#include <gtk/gtk.h>

GtkWidget *imageWidgetRGB;

static void set_img_to_pixbuf_rgb(GdkPixbuf *pixbuf)
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

  imgRGB = flip_horizontal_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}

static void on_flip_vertical_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  imgRGB = flip_vertical_rgb(imgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);
}

void setup_ui_rgb(GtkWidget *stack)
{
  // RGB Image Handling
  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), mainBox, "Manipulação RGB", "Manipulação RGB");

  GtkWidget *imageBoxRGB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), imageBoxRGB, TRUE, TRUE, 10);

  GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgRGB->dim.largura, imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbufGray);

  imageWidgetRGB = gtk_image_new_from_pixbuf(pixbufGray);
  gtk_box_pack_start(GTK_BOX(imageBoxRGB), imageWidgetRGB, TRUE, TRUE, 0);

  // Botões no menuBox
  GtkWidget *menuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), menuBox, TRUE, TRUE, 10);

  GtkWidget *flipHorizontalButtonGray = gtk_toggle_button_new_with_label("Flip Horizontal");
  g_signal_connect(flipHorizontalButtonGray, "toggled", G_CALLBACK(on_flip_horizontal_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipHorizontalButtonGray, FALSE, FALSE, 5);

  GtkWidget *flipVerticalButtonGray = gtk_toggle_button_new_with_label("Flip Vertical");
  g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(on_flip_vertical_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipVerticalButtonGray, FALSE, FALSE, 5);

  GtkWidget *transposeButtonGray = gtk_toggle_button_new_with_label("*Transpose*");
  g_signal_connect(transposeButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), transposeButtonGray, FALSE, FALSE, 5);

  GtkWidget *claheButtonGray = gtk_toggle_button_new_with_label("*filtro CLAHE*");
  g_signal_connect(claheButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), claheButtonGray, FALSE, FALSE, 5);

  GtkWidget *medianBlurButtonGray = gtk_toggle_button_new_with_label("*filtro Median Blur*");
  g_signal_connect(medianBlurButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), medianBlurButtonGray, FALSE, FALSE, 5);

  GtkWidget *rotate90ButtonGray = gtk_button_new_with_label("*Rotate 90º*");
  g_signal_connect(rotate90ButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate90ButtonGray, FALSE, FALSE, 5);

  GtkWidget *rotate_90ButtonGray = gtk_button_new_with_label("*Rotate -90º*");
  g_signal_connect(rotate_90ButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate_90ButtonGray, FALSE, FALSE, 5);

  GtkWidget *randomButton = gtk_button_new_with_label("*---Imagem Aleatória---*");
  g_signal_connect(randomButton, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), randomButton, FALSE, FALSE, 5);

  GtkWidget *aboutButton = gtk_button_new_with_label("❤️");
  g_signal_connect(aboutButton, "clicked", G_CALLBACK(on_about_button_clicked), aboutDialog);
  gtk_box_pack_start(GTK_BOX(menuBox), aboutButton, FALSE, FALSE, 5);
}
