#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Ler arquivos
void readFileGray()
{
    ImageGray *imageGray = malloc(sizeof(ImageGray));

    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("imageGray.txt", "r");
    if (arqGray == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqGray);
        exit(1);
    }

    if (fscanf(arqGray,"%d %d", &imageGray->dim.largura, &imageGray->dim.altura) !=2)
    {
        printf("erro na leitura da dimensão");
        fclose(arqGray);
        free(imageGray);
        exit(1);
    }

    fgetc(arqGray);

    //Alocando memoria
    imageGray->pixels = malloc(imageGray->dim.largura * imageGray->dim.altura * sizeof(PixelGray));
    if (imageGray->pixels == NULL)
    {
        printf("ERRO ao alocar pixels!\n");
        fclose(arqGray);
        free(imageGray);
        exit(1);
    }

    //Lendo os pixels
    for(int i = 0; i < imageGray->dim.largura * imageGray->dim.altura; i++)
    {
        int pixel;
        char separador;
        if(fscanf(arqGray, "%d%c", &pixel, &separador) != 2)
        {
            printf("erro na leitura do pixel\n");
            fclose(arqGray);
            free(imageGray->pixels);
            free(imageGray);
            exit(1);
        }

        //Atribuindo o valor do pixel
        imageGray->pixels[i].value = pixel;
        printf("%d ", imageGray->pixels[i].value);   
    }

    fclose(arqGray);
}

void readFileRGB()
{
    ImageRGB *imageRGB = malloc(sizeof(ImageRGB));

    //Criando arquivo
    FILE *arqRGB;
    arqRGB = fopen("imageRGB.txt", "r");
    if (arqRGB == NULL)
    {
        printf("ERRO ao abrir o arquivo!\n");
        fclose(arqRGB);
        exit(1);
    }
    if (fscanf(arqRGB,"%d %d", &imageRGB->dim.largura, &imageRGB->dim.altura) !=2)
    {
        printf("erro na leitura da dimensão");
        fclose(arqRGB);
        free(imageRGB);
        exit(1);
    }

    fgetc(arqRGB);

    //Alocando memoria
    imageRGB->pixels = malloc(imageRGB->dim.largura * imageRGB->dim.altura * sizeof(PixelRGB));
    if (imageRGB->pixels == NULL)
    {
        printf("ERRO ao alocar pixels!\n");
        fclose(arqRGB);
        free(imageRGB);
        exit(1);
    }

    //Lendo os pixels
    for(int i = 0; i < imageRGB->dim.largura * imageRGB->dim.altura; i++)
    {
        int r, g, b;
        char separador;
        if(fscanf(arqRGB, "%d %d %d%c", &r, &g, &b, &separador) != 4)
        {
            printf("erro na leitura do pixel\n");
            fclose(arqRGB);
            free(imageRGB->pixels);
            free(imageRGB);
            exit(1);
        }

        imageRGB->pixels[i].red = r;
        imageRGB->pixels[i].green = g;
        imageRGB->pixels[i].blue = b;
        printf("%d %d %d ", imageRGB->pixels[i].red, imageRGB->pixels[i].green, imageRGB->pixels[i].blue);   
    }

    fclose(arqRGB);
}


