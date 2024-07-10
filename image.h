#ifndef IMAGE_H
#define IMAGE_H

typedef struct dimensoes {
    int altura, largura;
} Dimensoes;

typedef struct pixelRGB {
    int red, blue, green;
    int value;
} PixelRGB;

typedef struct pixelGray {
    int value;
} PixelGray;

typedef struct imageGray {
    Dimensoes dim;
    PixelGray *pixels;
} ImageGray;

typedef struct imageRGB {
    Dimensoes dim;
    PixelRGB *pixels;
} ImageRGB;

typedef struct hGray{
    struct hGray *prox;
    ImageGray imgray;
} HGray;

typedef struct hRGB{
    struct hRGB *prox;
    ImageRGB imgrgb;
} HRGB;

typedef struct listagray{
    struct listagray *prox;
    struct listagray *ant;
    ImageGray *image;
    char *nome;
} Listagray;

typedef struct listargb{
    struct listargb *prox;
    struct listargb *ant;
    ImageRGB *image;
    char *nome;
} Listargb;

typedef struct{
    Listagray *cabeca;
    Listagray *corpo;
    Listagray *current;
} LinkedGray;

typedef struct{
    Listargb *cabeca;
    Listargb *corpo;
    Listargb *current;
} LinkedRGB;

typedef struct elementogray
{
    ImageGray *image;
    char *nome;
    struct elementogray *prox;
} ListRandomGray;

typedef struct elementorgb
{
    ImageRGB *image;
    char *nome;
    struct elementorgb *prox;
} ListRandomRGB;

// Ler arquivo
void readFileGray();
void readFileRGB();

// Funções de criação e liberação de struct
ImageGray *create_image_gray(int largura, int altura);
void free_image_gray(ImageGray *image);

ImageRGB *create_image_rgb(int largura, int altura);
void free_image_rgb(ImageRGB *image);

// Converter struct para txt
void convertGraytxt(ImageGray *image, int *numAlteracoes, char *nome, LinkedGray *l);
void convertRGBtxt(ImageRGB *image, int *numAlteracoes, char *nome, LinkedRGB *l);
void convertGrayRandomtxt(ImageGray *image, int *numAlteracoes, ListRandomGray **l);
void convertRGBRandomtxt(ImageRGB *image, int *numAlteracoes, ListRandomRGB **l);

// Operações para ImageGray
ImageGray *flip_vertical_gray(ImageGray *image);
ImageGray *flip_horizontal_gray(ImageGray *image);
ImageGray *transpose_gray(const ImageGray *image);
ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height);
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);
ImageGray *random_gray(ImageGray *image);

// Operações para ImageRGB
ImageRGB *flip_vertical_rgb(const ImageRGB *image);
ImageRGB *flip_horizontal_rgb(const ImageRGB *image);
ImageRGB *transpose_rgb(const ImageRGB *image);
ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height);
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);
ImageRGB *random_rgb(ImageRGB *image);

//Operações da Lista simples
ListRandomGray *create_list_random_gray();
void add_list_random_gray(ListRandomGray **l, ImageGray *image, char *nome);
void print_list_random_gray(ListRandomGray *l);
void free_random_gray(ListRandomGray *l);

ListRandomRGB *create_list_random_RGB();
void add_list_random_rgb(ListRandomRGB **l, ImageRGB *image, char *nome);
void print_list_random_rgb(ListRandomRGB *l);
void free_random_rgb(ListRandomRGB *l);

//Operação da Lista dupla
LinkedGray *criar_gray();
void adicionar_gray(LinkedGray *l, ImageGray *image, char *nome);
void liberar_gray(LinkedGray *l);
ImageGray *desfazer_gray(LinkedGray *l);
ImageGray *refazer_gray(LinkedGray *l);

LinkedRGB *criar_RGB();
void adicionar_rgb(LinkedRGB *l, ImageRGB *image, char *nome);
void liberar_rgb(LinkedRGB *l);
ImageRGB *desfazer_rgb(LinkedRGB *l);
ImageRGB *refazer_rgb(LinkedRGB *l);

//Chamada do python
void call_python_gray(int *numAlteracoes, char *nome);
void call_python_rgb(int *numAlteracoes, char *nome);

void call_python_historico_gray(char *nome);
void call_python_historico_rgb(char *nome);

void call_python_gray_random(int *numAlteracoes);
void call_python_rgb_random(int *numAlteracoes);

#endif // IMAGE_H
