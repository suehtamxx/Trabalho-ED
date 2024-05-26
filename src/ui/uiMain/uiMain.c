#include <imgRGB.h>
#include <imgGray.h>
#include <uiMain.h>
#include <uiRGB.h>
#include <gtk/gtk.h>

GtkWidget *imageWidgetRGB;
GtkWidget *imageWidgetGray;
ImageRGB *imgRGB;
ImageGray *imgGray;

int start(int argc, char *argv[])
{
  // imgRGB = set_imgRGB_from_arq("imgRGB.txt");
  // imgGray = set_imgRGB_from_arq("imgGray.txt");

  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

  GtkWidget *stack = gtk_stack_new();
  GtkWidget *stackSwitcher = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stackSwitcher), GTK_STACK(stack));

  GtkWidget *headerBar = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerBar), TRUE);
  gtk_window_set_titlebar(GTK_WINDOW(window), headerBar);

  gtk_header_bar_pack_start(GTK_HEADER_BAR(headerBar), stackSwitcher);

  GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(mainBox), stack, TRUE, TRUE, 1);

  gtk_container_add(GTK_CONTAINER(window), mainBox);

  setup_ui_rgb(stack);

  // Grayscale Image Handling
  GtkWidget *imageBoxGray = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_stack_add_titled(GTK_STACK(stack), imageBoxGray, "Manipulação Gray", "Manipulação Gray");

  // GdkPixbuf *pixbufGray = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, imgGray->dim.largura, imgGray->dim.altura);
  // set_img_to_pixbuf_gray(imgGray, pixbufGray);

  // imageWidgetGray = gtk_image_new_from_pixbuf(pixbufGray);
  // gtk_box_pack_start(GTK_BOX(imageBoxGray), imageWidgetGray, TRUE, TRUE, 0);

  // GtkWidget *buttonBoxGray = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  // gtk_box_pack_start(GTK_BOX(imageBoxGray), buttonBoxGray, FALSE, FALSE, 0);

  // GtkWidget *flipHorizontalButtonGray = gtk_button_new_with_label("Flip Horizontal Gray");
  // g_signal_connect(flipHorizontalButtonGray, "clicked", G_CALLBACK(on_flip_horizontal_gray_button_clicked), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonBoxGray), flipHorizontalButtonGray, TRUE, TRUE, 0);

  // GtkWidget *flipVerticalButtonGray = gtk_button_new_with_label("Flip Vertical Gray");
  // g_signal_connect(flipVerticalButtonGray, "clicked", G_CALLBACK(on_flip_vertical_gray_button_clicked), NULL);
  // gtk_box_pack_start(GTK_BOX(buttonBoxGray), flipVerticalButtonGray, TRUE, TRUE, 0);

  // About Dialog
  GtkWidget *aboutDialog = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutDialog), "Imagem RGB e Gray");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutDialog), "1.0");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutDialog), "Trabalho de Estrutura de Dados I");

  // Adicione a URL do site
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(aboutDialog), "https://github.com/usuario/repositorio");
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(aboutDialog), "GitHub");

  // Corrigido: Adicionado uma vírgula no final do array de autores
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(aboutDialog), (const gchar *[]){"Kauã Henrique", "Flavio Lima", "Rayssa Alves", NULL});
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(aboutDialog), GTK_LICENSE_GPL_3_0);
  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(aboutDialog), TRUE);
  gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(aboutDialog), "image-x-generic");

  GtkWidget *aboutButton = gtk_button_new_with_label("❤️");
  g_signal_connect(aboutButton, "clicked", G_CALLBACK(on_about_button_clicked), aboutDialog);
  gtk_box_pack_start(GTK_BOX(mainBox), aboutButton, FALSE, FALSE, 0);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

void on_about_button_clicked(GtkWidget *widget, gpointer data)
{
  (void)widget;

  GtkWidget *aboutDialog = GTK_WIDGET(data);
  gtk_dialog_run(GTK_DIALOG(aboutDialog));
  gtk_widget_hide(aboutDialog);
}

void on_window_destroy(GtkWidget *widget, gpointer data)
{
  (void)widget;
  (void)data;

  // free_image_rgb(imgRGB);
  gtk_main_quit();
}
