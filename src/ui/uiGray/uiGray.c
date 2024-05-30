#include <uiGray.h>
#include <imgGray.h>
#include <uiHistorico.h>
#include <uiMain.h>

GtkWidget *imageWidgetGray;
GtkWidget *navBoxGray;

static void verificarBotoes()
{
  GList *children = gtk_container_get_children(GTK_CONTAINER(navBoxGray));
  GtkWidget *forwardButton = GTK_WIDGET(g_list_nth_data(children, 2));
  GtkWidget *backButton = GTK_WIDGET(g_list_nth_data(children, 0));
  gtk_widget_set_sensitive(forwardButton, historicoGrayAtual->next != NULL);
  gtk_widget_set_sensitive(backButton, historicoGrayAtual->prev != NULL);
}

static void set_img_to_pixbuf_gray(GdkPixbuf *pixbuf)
{
  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

  for (int i = 0; i < historicoGrayAtual->imgGray->dim.altura; i++)
    for (int j = 0; j < historicoGrayAtual->imgGray->dim.largura; j++)
    {
      int index = (i * historicoGrayAtual->imgGray->dim.largura + j) * 3;
      pixels[index] = historicoGrayAtual->imgGray->pixels[i * historicoGrayAtual->imgGray->dim.largura + j].value;
      pixels[index + 1] = historicoGrayAtual->imgGray->pixels[i * historicoGrayAtual->imgGray->dim.largura + j].value;
      pixels[index + 2] = historicoGrayAtual->imgGray->pixels[i * historicoGrayAtual->imgGray->dim.largura + j].value;
    }
}

static void on_flip_horizontal_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = flip_horizontal_gray(historicoGrayAtual->imgGray);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_flip_vertical_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = flip_vertical_gray(historicoGrayAtual->imgGray);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_transpose_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = transpose_gray(historicoGrayAtual->imgGray);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_clahe_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = clahe_gray(historicoGrayAtual->imgGray, 8, 8);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_median_blur_gray_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = median_blur_gray(historicoGrayAtual->imgGray, 3);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_add90_rotation_gray_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = add90_rotation_gray(historicoGrayAtual->imgGray);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_neq90_rotation_gray_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  ImageGray *newImage = neq90_rotation_gray(historicoGrayAtual->imgGray);
  adicionarHistoricoGray(newImage);

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_back_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  VoltarHistoricoGray();

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

static void on_forward_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  SeguirHistoricoGray();

  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoGrayAtual->imgGray->dim.largura, historicoGrayAtual->imgGray->dim.altura);
  set_img_to_pixbuf_gray(pixbuf);

  gtk_image_set_from_pixbuf(GTK_IMAGE(imageWidgetGray), pixbuf);
  gtk_widget_show(imageWidgetGray);

  verificarBotoes();
}

void setup_ui_Gray(GtkWidget *stack)
{
  iniciarHistoricoGray();

  // RGB Image Handling
  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), mainBox, "Manipulação Gray", "Manipulação Gray");

  GtkWidget *imageBoxRGB = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), imageBoxRGB, TRUE, TRUE, 10);

  GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, historicoRGBAtual->imgRGB->dim.largura, historicoRGBAtual->imgRGB->dim.altura);
  set_img_to_pixbuf_gray(pixbufGray);

  imageWidgetGray = gtk_image_new_from_pixbuf(pixbufGray);
  gtk_box_pack_start(GTK_BOX(imageBoxRGB), imageWidgetGray, TRUE, TRUE, 0);

  // Botões no menuBox
  GtkWidget *menuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), menuBox, TRUE, TRUE, 10);

  GtkWidget *flipHorizontalButtonGray = gtk_button_new_with_label("Flip Horizontal");
  g_signal_connect(flipHorizontalButtonGray, "clicked", G_CALLBACK(on_flip_horizontal_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipHorizontalButtonGray, TRUE, TRUE, 5);

  GtkWidget *flipVerticalButtonGray = gtk_button_new_with_label("Flip Vertical");
  g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(on_flip_vertical_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), flipVerticalButtonGray, TRUE, TRUE, 5);

  GtkWidget *transposeButtonGray = gtk_button_new_with_label("Transpose");
  g_signal_connect(transposeButtonGray, "clicked", G_CALLBACK(on_transpose_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), transposeButtonGray, TRUE, TRUE, 5);

  GtkWidget *claheButtonGray = gtk_button_new_with_label("filtro CLAHE");
  g_signal_connect(claheButtonGray, "clicked", G_CALLBACK(on_clahe_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), claheButtonGray, TRUE, TRUE, 5);

  GtkWidget *medianBlurButtonGray = gtk_button_new_with_label("filtro Median Blur");
  g_signal_connect(medianBlurButtonGray, "clicked", G_CALLBACK(on_median_blur_gray_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), medianBlurButtonGray, TRUE, TRUE, 5);

  GtkWidget *rotate90ButtonGray = gtk_button_new_with_label("Rotate 90º");
  g_signal_connect(rotate90ButtonGray, "clicked", G_CALLBACK(on_add90_rotation_gray_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate90ButtonGray, TRUE, TRUE, 5);

  GtkWidget *rotate_90ButtonGray = gtk_button_new_with_label("Rotate -90º");
  g_signal_connect(rotate_90ButtonGray, "clicked", G_CALLBACK(on_neq90_rotation_gray_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), rotate_90ButtonGray, TRUE, TRUE, 5);

  GtkWidget *randomButton = gtk_button_new_with_label("---Imagem Aleatória---");
  g_signal_connect(randomButton, "clicked", G_CALLBACK(NULL), NULL);
  gtk_box_pack_start(GTK_BOX(menuBox), randomButton, TRUE, TRUE, 5);

  navBoxGray = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(menuBox), navBoxGray, TRUE, TRUE, 5);

  GtkWidget *backButton = gtk_button_new_with_label("<");
  g_signal_connect(backButton, "clicked", G_CALLBACK(on_back_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(navBoxGray), backButton, TRUE, TRUE, 5);

  GtkWidget *aboutButton = gtk_button_new_with_label("❤️");
  g_signal_connect(aboutButton, "clicked", G_CALLBACK(on_about_button_clicked), aboutDialog);
  gtk_box_pack_start(GTK_BOX(navBoxGray), aboutButton, TRUE, TRUE, 5);

  GtkWidget *forwardButton = gtk_button_new_with_label(">");
  g_signal_connect(forwardButton, "clicked", G_CALLBACK(on_forward_button_clicked), NULL);
  gtk_box_pack_start(GTK_BOX(navBoxGray), forwardButton, TRUE, TRUE, 5);

  verificarBotoes();
}
