#include <imgGray.h>
#include <stdio.h>

ImageGray *create_image_gray(int largura, int altura)
{
  ImageGray *img = calloc(sizeof(ImageGray));
  img->dim.altura = altura;
  img->dim.largura = largura;
  img->pixels = calloc((largura * altura), sizeof(PixelGray));

  return img;
}
void free_image_gray(ImageGray *image)
{
  if (image)
  {
    free(image->pixels);
    free(image);
  }
}

void helloWord()
{
  printf("Hello, World!\n");
}