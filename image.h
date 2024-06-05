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
    ImageGray imgGray;
} Listagray;

typedef struct listargb{
    struct listargb *prox;
    struct listargb *ant;
    ImageRGB imgRGB;
} Listargb;

// Ler arquivo
void readFileGray();
void readFileRGB();

// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura);
void free_image_gray(ImageGray *image);

ImageRGB *create_image_rgb(int largura, int altura);
void free_image_rgb(ImageRGB *image);

// Converter struct para txt
void convertGraytxt(ImageGray *image, int *numAlteracoes);
void convertRGBtxt(ImageRGB *image, int *numAlteracoes);

// Operações para ImageGray
ImageGray *flip_vertical_gray(ImageGray *image);
ImageGray *flip_horizontal_gray(ImageGray *image);
ImageGray *transpose_gray(const ImageGray *image);

// Operações para ImageRGB
ImageRGB *flip_vertical_rgb(const ImageRGB *image);
ImageRGB *flip_horizontal_rgb(const ImageRGB *image);
ImageRGB *transpose_rgb(const ImageRGB *image);

// Manipulação por pixel para ImageGray
ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height);
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);

// Manipulação por pixel para ImageRGB
ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height);
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);

#endif // IMAGE_H
