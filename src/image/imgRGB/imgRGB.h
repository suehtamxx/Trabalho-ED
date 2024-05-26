#pragma once

#include <imgStruct.h>

 ImageRGB *create_image_rgb(int largura, int altura);
void free_image_rgb(ImageRGB *image);


// // Operações para ImageRGB
// ImageRGB *flip_vertical_rgb(const ImageRGB *image);
// ImageRGB *flip_horizontal_rgb(const ImageRGB *image);
// ImageRGB *transpose(const ImageRGB *image);


// // Manipulação por pixel para ImageRGB
// ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height);
// ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);
