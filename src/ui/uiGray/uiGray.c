#include <uiGray.h>
#include <imgGray.h>
#include <uiMain.h>

void setup_ui_Gray(GtkWidget *stack)
{
  // RGB Image Handling
  GtkWidget *imageBoxGray = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), imageBoxGray, "Manipulação Gray", "Manipulação Gray");

  // GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  // set_img_to_pixbuf_Gray(imgGray, pixbufGray);

  // imageWidgetGray = gtk_image_new_from_pixbuf(pixbufGray);
  // gtk_box_pack_start(GTK_BOX(imageBoxGray), imageWidgetGray, TRUE, TRUE, 0);

  // butons for manipulation
  GtkWidget *buttonFlip = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), buttonFlip, FALSE, FALSE, 2);

  GtkWidget *flipHorizontalButtonGray = gtk_toggle_button_new_with_label("Flip Horizontal");
  g_signal_connect(flipHorizontalButtonGray, "toggled", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonFlip), flipHorizontalButtonGray, TRUE, TRUE, 0);

  GtkWidget *flipVerticalButtonGray = gtk_toggle_button_new_with_label("Flip Vertical");
  g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonFlip), flipVerticalButtonGray, TRUE, TRUE, 0);

  GtkWidget *transposeButtonGray = gtk_toggle_button_new_with_label("Transpose");
  g_signal_connect(transposeButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonFlip), transposeButtonGray, TRUE, TRUE, 0);

  // buttons for rotation
  GtkWidget *buttonRotation = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), buttonRotation, FALSE, FALSE, 2);

  GtkWidget *rotate90ButtonGray = gtk_button_new_with_label("Rotate 90º");
  g_signal_connect(rotate90ButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonRotation), rotate90ButtonGray, TRUE, TRUE, 0);

  GtkWidget *rotate180ButtonGray = gtk_button_new_with_label("Rotate -90º");
  g_signal_connect(rotate180ButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonRotation), rotate180ButtonGray, TRUE, TRUE, 0);

  // filters
  GtkWidget *buttonFilters = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), buttonFilters, FALSE, FALSE, 2);

  GtkWidget *claheButtonGray = gtk_toggle_button_new_with_label("filtro CLAHE");
  g_signal_connect(claheButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonFilters), claheButtonGray, TRUE, TRUE, 0);

  GtkWidget *medianBlurButtonGray = gtk_toggle_button_new_with_label("filtro Median Blur");
  g_signal_connect(medianBlurButtonGray, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(buttonFilters), medianBlurButtonGray, TRUE, TRUE, 0);

  // Gerar uma linha
  GtkWidget *line = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), line, FALSE, FALSE, 2);

  // Butão para imagem aleatória
  GtkWidget *randomButton = gtk_button_new_with_label("---Imagem Aleatória---");
  g_signal_connect(randomButton, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), randomButton, FALSE, FALSE, 2);

  int button_width = 200;
  gtk_widget_set_size_request(flipHorizontalButtonGray, button_width, -1);
  gtk_widget_set_size_request(flipVerticalButtonGray, button_width, -1);
  gtk_widget_set_size_request(transposeButtonGray, button_width, -1);
  gtk_widget_set_size_request(rotate90ButtonGray, button_width, -1);
  gtk_widget_set_size_request(rotate180ButtonGray, button_width, -1);
  gtk_widget_set_size_request(claheButtonGray, button_width, -1);
  gtk_widget_set_size_request(medianBlurButtonGray, button_width, -1);
  gtk_widget_set_size_request(randomButton, button_width, -1);
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
