#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    ImageGray *imageGray = malloc(sizeof(imageGray));
    //ImageRGB *imageRGB = NULL;
    if (imageGray == NULL)
    {
        printf("ERRO ao alocar!\n");
        exit(1);
    }
    
    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("imageGray.txt", "r");
    if (arqGray == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqGray);
        exit(1);
    }

    //Retirando as dimensoes
    fscanf(arqGray, "%d", &imageGray->dim.largura);
    fscanf(arqGray, "%d", &imageGray->dim.altura);

    imageGray = create_image_gray(imageGray->dim.largura, imageGray->dim.altura);

    fclose(arqGray);

    //free_image_gray(imageGray);

    ImageRGB *imageRGB = malloc(sizeof(ImageRGB));
    //ImageRGB *imageRGB = NULL;
    if (imageRGB == NULL)
    {
        printf("ERRO ao alocar!\n");
        exit(1);
    }
    
    //Criando arquivo
    FILE *arqRGB;
    arqRGB = fopen("imageRGB.txt", "r");
    if (arqRGB == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqRGB);
        exit(1);
    }

    //Retirando as dimensoes
    fscanf(arqRGB, "%d", &imageRGB->dim.largura);
    fscanf(arqRGB, "%d", &imageRGB->dim.altura);

    imageRGB = create_image_rgb(imageRGB->dim.largura, imageRGB->dim.altura);

    fclose(arqRGB);
    return 0;
}