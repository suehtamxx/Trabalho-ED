#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura)
{
    ImageGray *image;

    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("input_image_example_RGB.txt", "r");
    if (arqGray == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        return;
    }

    //Retirando as dimensoes
    fscanf(arqGray, "%d", &image->dim.largura);
    fscanf(arqGray, "%d", &image->dim.altura);
    

    //Alocando memoria
    
    
    return image;
}

void free_image_gray(ImageGray *image)
{
    free(image);
}
