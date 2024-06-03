#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ImageGray *imageGray;
    //ImageRGB *imageRGB;

    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("./input_image_example_RGB.txt", "r");
    if (arqGray == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        exit(1);
    }

    //Retirando as dimensoes
    fscanf(arqGray, "%d", &imageGray->dim.largura);
    fscanf(arqGray, "%d", &imageGray->dim.altura);

    imageGray = create_image_gray(imageGray->dim.largura, imageGray->dim.altura);

    fclose(arqGray);

    free_image_gray(imageGray);

    return 0;
}