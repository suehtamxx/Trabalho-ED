#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Ler arquivos
void readFileGray(ImageGray *imageGray, FILE *arqGray)
{ 
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
        //printf("%d ", imageGray->pixels[i].value);   
    }
}
void readFileRGB(ImageRGB *imageRGB, FILE *arqRGB)
{
    //Lendo os pixels
    for(int i = 0; i < imageRGB->dim.largura * imageRGB->dim.altura; i++)
    {
        int r, g, b;
        char separador;
        if(fscanf(arqRGB, "%d %d %d%c", &r, &g, &b, &separador) != 4)
        {
            printf("ERRO na leitura do pixel\n");
            free(imageRGB->pixels);
            free(imageRGB);
            fclose(arqRGB);
            exit(1);
        }
        
        //Atribuindo o valor do pixel
        imageRGB->pixels[i].red = r;
        imageRGB->pixels[i].green = g;
        imageRGB->pixels[i].blue = b;
        //printf("%d %d %d ", imageRGB->pixels[i].red, imageRGB->pixels[i].green, imageRGB->pixels[i].blue);   
    }
}

LinkedRGB *criar_RGB()
{
    LinkedRGB *l = malloc(sizeof(LinkedRGB));
    if(l == NULL){
        printf("erro ao alocar");
        exit(1);
    }
    l->cabeca = NULL;
    l->corpo = NULL;
    return l;
}

void adicionar_rgb(LinkedRGB *l, ImageRGB *image)
{
    Listargb *novo = malloc(sizeof(Listargb));
    if(novo == NULL){
        printf("erro ao alocar!");
        exit(1);
    }
    novo->image = image;
    novo->prox = NULL;
    novo->ant = l->corpo;
    if(l->corpo != NULL){
        l->corpo->prox = novo;
    } else {
        l->cabeca = novo;
    }
    l->corpo = novo;
}

void liberar_rgb(LinkedRGB *l)
{
    Listargb *aux = l->cabeca;
    while(aux != NULL){
        Listargb *prox = aux->prox;
        free(aux->image->pixels);
        free(aux->image);
        free(aux);
        aux = prox;
    }
    free(l);
}

LinkedGray *criar_gray()
{
    LinkedGray *l = malloc(sizeof(LinkedGray));
    if(l == NULL){
        printf("erro ao alocar");
        exit(1);
    }
    l->cabeca = NULL;
    l->corpo = NULL;
    return l;
}

void adicionar_gray(LinkedGray *l, ImageGray *image)
{
    Listagray *novo = malloc(sizeof(Listagray));
    if(novo == NULL){
        printf("erro ao alocar!");
        exit(1);
    }
    novo->image = image;
    novo->prox = NULL;
    novo->ant = l->corpo;
    if(l->corpo != NULL){
        l->corpo->prox = novo;
    } else {
        l->cabeca = novo;
    }
    l->corpo = novo;
}

void liberar_gray(LinkedGray *l)
{
    Listagray *aux = l->cabeca;
    while(aux != NULL){
        Listagray *prox = aux->prox;
        free(aux->image->pixels);
        free(aux->image);
        free(aux);
        aux = prox;
    }
    free(l);
}


// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura)
{
    //Alocando struct
    ImageGray *image = malloc(sizeof(ImageGray));
    if (image == NULL)
    {
        printf("ERRO ao alocar struct gray!\n");
        exit(1);
    }

    //Atribuindo os valores a struct
    image->dim.largura = largura;
    image->dim.altura = altura;
    //printf("Dimensoes: %d %d", image->dim.largura, image->dim.altura);

    //Alocanco os pixels
    image->pixels = malloc((largura * altura) * sizeof(PixelGray));
    if (image->pixels == NULL)
    {
        printf("ERRO ao alocar pixels da struct gray!\n");
        free(image);
        exit(1);
    }
    
    return image;
}
void free_image_gray(ImageGray *image)
{
    free(image->pixels);
    free(image);
}

ImageRGB *create_image_rgb(int largura, int altura)
{
    //Alocando struct
    ImageRGB *image = malloc(sizeof(ImageRGB));
    if (image == NULL)
    {
        printf("ERRO ao alocar struct rgb!\n");
        exit(1);
    }

    //Atribuindo os valores a struct
    image->dim.largura = largura;
    image->dim.altura = altura;
    //printf("Dimensoes: %d %d", image->dim.largura, image->dim.altura);

    //Alocanco os pixels
    image->pixels = malloc((largura * altura) * sizeof(PixelRGB));
    if (image->pixels == NULL)
    {
        printf("ERRO ao alocar pixels da struct rgb!\n");
        free(image);
        exit(1);
    }
    
    return image;
}
void free_image_rgb(ImageRGB *image)
{
    free(image->pixels);
    free(image);
}

// Converter struct para txt
void convertGraytxt(ImageGray *image)
{
    //Criando o arquivo
    FILE *arqGray;
    arqGray = fopen("transposeGray.txt", "w");
    if (arqGray == NULL)
    {
        printf("ERRO ao criar arquivo.\n");
        exit(1);
    }

    //Escrevendo as dimensões no arquivo
    fprintf(arqGray, "%d\n", image->dim.largura);
    fprintf(arqGray, "%d\n", image->dim.altura);
    
    //Escrevendo os pixels no arquivo
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            if (j == image->dim.largura - 1) fprintf(arqGray, "%d,\n", image->pixels[i * image->dim.largura + j].value);
            else fprintf(arqGray, "%d, ", image->pixels[i * image->dim.largura + j].value);
        }
    }
    
    fclose(arqGray);
}
void convertRGBtxt(ImageRGB *image)
{
    //Criando o arquivo
    FILE *arqRGB;
    arqRGB = fopen("transposeRGB.txt", "w");
    if (arqRGB == NULL) 
    {
        printf("ERRO ao criar arquivo.\n");
        exit(1);
    }

    //Escrevendo as dimensões no arquivo
    fprintf(arqRGB, "%d\n", image->dim.largura);
    fprintf(arqRGB, "%d\n", image->dim.altura);
    
    //Escrevendo os pixels no arquivo
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            PixelRGB pixel = image->pixels[i * image->dim.largura + j];
            if (j == image->dim.largura - 1) fprintf(arqRGB, "%d %d %d,\n", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
            else fprintf(arqRGB, "%d %d %d, ", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
        }
    }
    
    fclose(arqRGB);
}

// Operações para ImageGray
ImageGray *transpose_gray(const ImageGray *image)
{
    ImageGray *image_transpose = malloc(sizeof(ImageGray));
    if(image_transpose == NULL)
    {
        printf("ERRO ao alocar trasnpose gray!");
        exit(1);
    }

    image_transpose->dim.largura = image->dim.altura;
    image_transpose->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    image_transpose->pixels = malloc(image_transpose->dim.altura * image_transpose->dim.largura * sizeof(PixelGray));
    if(image_transpose->pixels == NULL)
    {
        printf("ERRO ao alocar pixels transpose gray!");
        free(image_transpose);
        exit(1);
    }

    for(int i = 0; i < image_transpose->dim.altura; i++)
    {
        for(int j = 0; j < image_transpose->dim.largura; j++)
        {
            image_transpose->pixels[i * image_transpose->dim.largura + j] = image->pixels[j * image->dim.altura + i];
            //printf("%d ", image_transpose->pixels[i * image->dim.largura + j].value);
        }    
    }

    return image_transpose;
}

// Operações para ImageRGB
ImageRGB *transpose_rgb(const ImageRGB *image)
{
    ImageRGB *image_transpose = malloc(sizeof(ImageRGB));
    if(image_transpose == NULL)
    {
        printf("ERRO ao alocar trasnpose rgb!");
        exit(1);
    }

    image_transpose->dim.largura = image->dim.altura;
    image_transpose->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    image_transpose->pixels = malloc(image_transpose->dim.altura * image_transpose->dim.largura * sizeof(PixelRGB));
    if(image_transpose->pixels == NULL)
    {
        printf("ERRO ao alocar pixels transpose rgb!");
        free(image_transpose);
        exit(1);
    }

    for(int i = 0; i < image_transpose->dim.altura; i++)
    {
        for(int j = 0; j < image_transpose->dim.largura; j++)
        {
            image_transpose->pixels[i * image_transpose->dim.largura + j] = image->pixels[j * image->dim.altura + i];
            //printf("%d %d %d ", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
        }    
    }

    return image_transpose;
}

