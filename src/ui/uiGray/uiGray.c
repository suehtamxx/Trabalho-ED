#include <uiGray.h>
#include <imgGray.h>
#include <uiMain.h>

GtkWidget *imageWidgetGray;

static void set_img_to_pixbuf_gray(GdkPixbuf *pixbuf)
{
  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

  for (int i = 0; i < imgGray->dim.altura; i++)
  {
    for (int j = 0; j < imgGray->dim.largura; j++)
    {
      int index = (i * imgGray->dim.largura + j) * 3;
      pixels[index] = imgGray->pixels[i * imgGray->dim.largura + j].value;
      pixels[index + 1] = imgGray->pixels[i * imgGray->dim.largura + j].value;
      pixels[index + 2] = imgGray->pixels[i * imgGray->dim.largura + j].value;
    }
  }
}

static void on_flip_horizontal_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  imgGray = flip_horizontal_gray(imgGray);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);
}

static void on_flip_vertical_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  imgGray = flip_vertical_gray(imgGray);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);
}

static void on_transpose_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  imgGray = transpose_gray(imgGray);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);
}

void setup_ui_Gray(GtkWidget *stack)
{
  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), mainBox, "Manipulação Gray", "Manipulação Gray");

  // Contêiner para a imagem à direita
  GtkWidget *imageBoxGray = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), imageBoxGray, TRUE, TRUE, 10);

  GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbufGray);
  imageWidgetGray = gtk_image_new_from_pixbuf(pixbufGray);
  gtk_box_pack_start(GTK_BOX(imageBoxGray), imageWidgetGray, TRUE, TRUE, 0);

  // Botões no menuBox
  GtkWidget *menuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), menuBox, TRUE, TRUE, 10);

  GtkWidget *flipHorizontalButtonGray = gtk_toggle_button_new_with_label("Flip Horizontal");
  g_signal_connect(flipHorizontalButtonGray, "toggled", G_CALLBACK(on_flip_horizontal_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipHorizontalButtonGray, FALSE, FALSE, 5);

  GtkWidget *flipVerticalButtonGray = gtk_toggle_button_new_with_label("Flip Vertical");
  g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(on_flip_vertical_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipVerticalButtonGray, FALSE, FALSE, 5);

  GtkWidget *transposeButtonGray = gtk_toggle_button_new_with_label("Transpose");
  g_signal_connect(transposeButtonGray, "clicked", G_CALLBACK(on_transpose_gray_button_clicked), NULL);
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
