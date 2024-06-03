#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura)
{
    ImageGray *imageGray = malloc(sizeof(imageGray));

    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("imageGray.txt", "r");
    if (arqGray == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqGray);
        exit(1);
    }

    //Alocando memoria
    imageGray->pixels = (PixelGray*)malloc((largura * altura) * sizeof(PixelGray));
    if (imageGray->pixels == NULL)
    {
        printf("ERRO ao alocar pixels!\n");
        exit(1);
    }

    //Lendo do arquivo e colocando na struct
    for (int i = 0; i < altura * largura; i++)
    {
        int pixel;
        if (fscanf(arqGray, "%d", &pixel) != 1)
        {
            printf("ERRO ao ler pixel.\n");
            free(imageGray->pixels);
            free(imageGray);
            exit(1);
        }

        imageGray->pixels[i].value = pixel;
        printf("%d ", imageGray->pixels[i].value);        
    }

    fclose(arqGray);
    
    return imageGray;
}

void free_image_gray(ImageGray *image)
{
    free(image);
}
