#include <imgGray.h>
#include <stdio.h>

ImageGray *create_image_gray(int largura, int altura){
  ImageGray *imggray = (ImageGray*)malloc(sizeof(ImageGray));
  imggray->dim.altura = altura;
  imggray->dim.largura = largura;
  //imggray->pixels 
}

void helloWord()
{
  printf("Hello, World!\n");
}