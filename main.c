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

    return 0;
}