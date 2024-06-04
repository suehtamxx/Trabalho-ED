#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ImageGray *imageGray = malloc(sizeof(ImageGray));
    ImageRGB *imageRGB = malloc(sizeof(ImageRGB));
    if (imageGray == NULL || imageRGB == NULL)
    {
        printf("ERRO ao alocar!\n");
        exit(1);
    }
    
    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("imageGray.txt", "r");
    FILE *arqRGB;
    arqRGB = fopen("imageRGB.txt", "r");
    if (arqGray == NULL || arqRGB == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqGray);
        exit(1);
    }

    fclose(arqGray);
    fclose(arqRGB);
    
    readFileGray();
    readFileRGB();


    //free_image_gray(imageGray);

    return 0;
}