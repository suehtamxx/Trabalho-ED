#pragma once

#include <imgStruct.h>

void helloWord();


// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura);
void free_image_gray(ImageGray *image);
ImageGray *read_image_gray_from_file(const char *filename);

// Operações para ImageGray
ImageGray *flip_vertical_gray(ImageGray *image);
ImageGray *flip_horizontal_gray(ImageGray *image);
ImageGray *transpose_gray(const ImageGray *image);

// Manipulação por pixel para ImageGray

//funçoes auxiliares para filtro clahe_gray

void calcula_histograma(const PixelGray *regiao, int width, int height, int *histograma);
void limite_Histograma(int *histograma, float limite);
void calcula_cdf(const int *histograma, float *cdf);
void equalizar_regiao(PixelGray *regiao, int width, int height, const float *cfd);

ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height);

//funçoes auxiliares para filtro median_blur_gray


ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);
