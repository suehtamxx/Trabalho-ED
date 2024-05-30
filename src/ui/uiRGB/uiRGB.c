#include <uiRGB.h>
#include <uiHistorico.h>
#include <imgRGB.h>
#include <uiMain.h>
#include <gtk/gtk.h>

GtkWidget *imageWidgetRGB;
GtkWidget *navBox;

static void verificarBotoes()
{
  GList *children = gtk_container_get_children(GTK_CONTAINER(navBox));
  GtkWidget *forwardButton = GTK_WIDGET(g_list_nth_data(children, 2));
  GtkWidget *backButton = GTK_WIDGET(g_list_nth_data(children, 0));
  gtk_widget_set_sensitive(forwardButton, historicoRGBAtual->next != NULL);
  gtk_widget_set_sensitive(backButton, historicoRGBAtual->prev != NULL);
}

static void set_img_to_pixbuf_rgb(GdkPixbuf *pixbuf)
{
  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

  for (int i = 0; i < historicoRGBAtual->imgRGB->dim.altura; i++)
    for (int j = 0; j < historicoRGBAtual->imgRGB->dim.largura; j++)
    {
      int index = (i * historicoRGBAtual->imgRGB->dim.largura + j) * 3;
      pixels[index] = historicoRGBAtual->imgRGB->pixels[i * historicoRGBAtual->imgRGB->dim.largura + j].red;
      pixels[index + 1] = historicoRGBAtual->imgRGB->pixels[i * historicoRGBAtual->imgRGB->dim.largura + j].green;
      pixels[index + 2] = historicoRGBAtual->imgRGB->pixels[i * historicoRGBAtual->imgRGB->dim.largura + j].blue;
    }
}

static void on_flip_horizontal_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = flip_horizontal_rgb(historicoRGBAtual->imgRGB);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_flip_vertical_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = flip_vertical_rgb(historicoRGBAtual->imgRGB);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_transpose_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = transpose_rgb(historicoRGBAtual->imgRGB);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static on_filter_clahe_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = clahe_rgb(historicoRGBAtual->imgRGB, 8, 8);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_filter_median_rgb_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = median_blur_rgb(historicoRGBAtual->imgRGB, 3);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_add90_rotation_rgb_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = add90_rotation_RGB(historicoRGBAtual->imgRGB);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_neq90_rotation_rgb_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageRGB *newImgRGB = neq90_rotation_RGB(historicoRGBAtual->imgRGB);
  adicionarHistoricoRGB(newImgRGB);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_back_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  VoltarHistoricoRGB();

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

static void on_forward_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;

  SeguirHistoricoRGB();

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetRGB), pixbuf);
  gtk_widget_show(imageWidgetRGB);

  verificarBotoes();
}

void setup_ui_rgb(GtkWidget *stack)
{
  iniciarHistoricoRGB();

  // RGB Image Handling
  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), mainBox, "Manipulação RGB", "Manipulação RGB");

  GtkWidget *imageBoxRGB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), imageBoxRGB, FALSE, FALSE, 10);

  GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_rgb(pixbufGray);

  imageWidgetRGB = gtk_image_new_from_pixbuf(pixbufGray);
  gtk_box_pack_start(GTK_BOX(imageBoxRGB), imageWidgetRGB, FALSE, FALSE, 0);

  // Botões no menuBox
  GtkWidget *menuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), menuBox, TRUE, TRUE, 10);

  GtkWidget *flipHorizontalButtonGray = gtk_button_new_with_label("Flip Horizontal");
  g_signal_connect(flipHorizontalButtonGray, "clicked", G_CALLBACK(on_flip_horizontal_rgb_button_clicked), NULL);
  g_signal_connect(flipHorizontalButtonGray, "clicked", G_CALLBACK(verificarBotoes), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipHorizontalButtonGray, TRUE, TRUE, 5);

  GtkWidget *flipVerticalButtonGray = gtk_button_new_with_label("Flip Vertical");
  g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(on_flip_vertical_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipVerticalButtonGray, TRUE, TRUE, 5);

  GtkWidget *transposeButtonGray = gtk_button_new_with_label("Transpose");
  g_signal_connect(transposeButtonGray, "clicked", G_CALLBACK(on_transpose_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), transposeButtonGray, TRUE, TRUE, 5);

  GtkWidget *claheButtonGray = gtk_button_new_with_label("filtro CLAHE");
  g_signal_connect(claheButtonGray, "clicked", G_CALLBACK(on_filter_clahe_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), claheButtonGray, TRUE, TRUE, 5);

  GtkWidget *medianBlurButtonGray = gtk_button_new_with_label("filtro Median Blur");
  g_signal_connect(medianBlurButtonGray, "clicked", G_CALLBACK(on_filter_median_rgb_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), medianBlurButtonGray, TRUE, TRUE, 5);

  GtkWidget *rotate90ButtonGray = gtk_button_new_with_label("Rotate 90º");
  g_signal_connect(rotate90ButtonGray, "clicked", G_CALLBACK(on_add90_rotation_rgb_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate90ButtonGray, TRUE, TRUE, 5);

  GtkWidget *rotate_90ButtonGray = gtk_button_new_with_label("Rotate -90º");
  g_signal_connect(rotate_90ButtonGray, "clicked", G_CALLBACK(on_neq90_rotation_rgb_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate_90ButtonGray, TRUE, TRUE, 5);

  GtkWidget *randomButton = gtk_button_new_with_label("---Imagem Aleatória---");
  g_signal_connect(randomButton, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), randomButton, TRUE, TRUE, 5);

  navBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(menuBox), navBox, TRUE, TRUE, 5);

  GtkWidget *backButton = gtk_button_new_with_label("<");
  g_signal_connect(backButton, "clicked", G_CALLBACK(on_back_button_clicked), navBox);
  gtk_box_pack_start(GTK_BOX(navBox), backButton, TRUE, TRUE, 5);

  GtkWidget *aboutButton = gtk_button_new_with_label("❤️");
  g_signal_connect(aboutButton, "clicked", G_CALLBACK(on_about_button_clicked), aboutDialog);
  gtk_box_pack_start(GTK_BOX(navBox), aboutButton, TRUE, TRUE, 5);

  GtkWidget *forwardButton = gtk_button_new_with_label(">");
  g_signal_connect(forwardButton, "clicked", G_CALLBACK(on_forward_button_clicked), navBox);
  gtk_box_pack_start(GTK_BOX(navBox), forwardButton, TRUE, TRUE, 5);

  verificarBotoes();
}
