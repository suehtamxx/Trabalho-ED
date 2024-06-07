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

// Funcções de criação e liberação de listas
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

// Funções de criação e liberação de struct
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
void convertGraytxt(ImageGray *image, int *numAlteracoes)
{
    //Criando nome do arquivo
    char NomeArq[25];
    sprintf(NomeArq, "../AlteracaoGray%d.txt", *numAlteracoes);
    //printf("%d", *numAlteracoes);
    (*numAlteracoes)++;

    //Criando o arquivo
    FILE *arqGray;
    arqGray = fopen(NomeArq, "w");
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
void convertRGBtxt(ImageRGB *image, int *numAlteracoes)
{
    //Criando nome do arquivo
    char NomeArq[25];
    sprintf(NomeArq, "../AlteracaoRGB%d.txt", *numAlteracoes);
    //printf("%d", *numAlteracoes);
    (*numAlteracoes)++;

    //Criando o arquivo
    FILE *arqRGB;
    arqRGB = fopen(NomeArq, "w");
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
            if (j == image->dim.largura - 1) fprintf(arqRGB, "%d %d %d,\n", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
            else fprintf(arqRGB, "%d %d %d, ", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
        }
    }
    
    fclose(arqRGB);
}

// Operações para ImageGray
ImageGray *transpose_gray(const ImageGray *image)
{
    //Criando struct nova
    ImageGray *image_transpose = malloc(sizeof(ImageGray));
    if(image_transpose == NULL)
    {
        printf("ERRO ao alocar trasnpose gray!");
        exit(1);
    }

    //Atribuindo as dimensoes para a struct nova
    image_transpose->dim.largura = image->dim.altura;
    image_transpose->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    //Alocando os pixels
    image_transpose->pixels = malloc(image_transpose->dim.altura * image_transpose->dim.largura * sizeof(PixelGray));
    if(image_transpose->pixels == NULL)
    {
        printf("ERRO ao alocar pixels transpose gray!");
        free(image_transpose);
        exit(1);
    }

    //Trocando as linhas pelas colunas
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
ImageGray *flip_horizontal_gray(ImageGray *image)
{
    //Criando struct nova
    ImageGray *image_horizontal = malloc(sizeof(ImageGray));
    if(image_horizontal == NULL)
    {
        printf("ERRO ao alocar flip horizontal gray!");
        exit(1);
    }

    //Atribuindo as dimensoes para a struct nova
    image_horizontal->dim.largura = image->dim.altura;
    image_horizontal->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    //Alocando os pixels
    image_horizontal->pixels = malloc(image_horizontal->dim.altura * image_horizontal->dim.largura * sizeof(PixelGray));
    if(image_horizontal->pixels == NULL)
    {
        printf("ERRO ao alocar pixels flip horizontal gray!");
        free(image_horizontal);
        exit(1);
    }

    for (int i = 0; i < image_horizontal->dim.altura; i++)
    {
        for (int j = 0; j < image_horizontal->dim.largura; j++)
        {
            image_horizontal->pixels[i * image_horizontal->dim.largura + j] = image->pixels[i * image->dim.largura + (image->dim.largura - j - 1)];
            //printf("%d ", image_horizontal->pixels[i * image_horizontal->dim.largura + j].value);
        }
    }
    
    return image_horizontal;
}
ImageGray *flip_vertical_gray(ImageGray *image)
{
    ImageGray *flip_image = malloc(sizeof(ImageGray));
    if(flip_image == NULL){
        printf("erro ao alocar flip vertical gray!\n");
        exit(1);
    }

    flip_image->dim.altura = image->dim.altura;
    flip_image->dim.largura = image->dim.largura;
    printf("Dimensoes: %d %d", flip_image->dim.largura, flip_image->dim.altura);

    flip_image->pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelGray));
    if(flip_image->pixels == NULL){
        printf("erro ao alocar pixels flip vertical gray!\n");
        free(flip_image);
        exit(1);
    }
    for(int i = 0; i < image->dim.altura; i++)
    {
        for(int j = 0; j < image->dim.largura; j++)
        {
            flip_image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j];
            //printf("%d ", flip_image->pixels[i * flip_image->dim.largura + j].value);
        }
    }
    return flip_image;
}
ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height)
{
    int largura = image->dim.largura;
    int altura = image->dim.altura;

    ImageGray *clahe = malloc(sizeof(ImageGray));
    if(clahe == NULL){
        printf("erro ao alocar");
        exit(1);
    }

    clahe->dim.largura = largura;
    clahe->dim.altura = altura;
    clahe->pixels = malloc(largura * altura * sizeof(PixelGray));
    if(clahe->pixels == NULL){
        printf("erro ao alocar");
        free(clahe);
        exit(1);
    }

    //"funcao" para definir o limite
    int n_tilesx = (largura + tile_width - 1) / tile_width;
    int n_tilesy = (altura + tile_height - 1) / tile_height;
    int lim = (tile_width * tile_height) / 8; //vc define seu limite

    //aqui vai percorrer cada bloco
    //iy itera sobre as linhas de blocos
    //n_tilesy é numero total de blocos na direçao vertical
    //jx itera sobre as colunas dos blocos
    //n_tilesx é o numero total de blocos na direcao horizontal
    for(int iy = 0; iy < n_tilesy; iy++)
    {
        for(int jx = 0; jx < n_tilesx; jx++)
        {
            int x_inicio = jx * tile_width;
            int y_inicio = iy * tile_height;
            int x_fim = (x_inicio + tile_width > largura) ? largura : x_inicio + tile_width;
            int y_fim = (y_inicio + tile_height > altura) ? altura : y_inicio + tile_height;

            //declara o histograma
            int hist[256] = {0};

            //calculo do histograma para o bloco atual
            for(int i = y_inicio; i < y_fim; i++)
            {
                for(int j = x_inicio; j < x_fim; j++)
                {
                    hist[image->pixels[i * largura + j].value]++;
                }
            }

            //"funcao" para limitar o histograma
            int excesso = 0;
            for(int i = 0; i < 256; i++)
            {
                if(hist[i] > lim){
                    excesso += hist[i] - lim;
                    hist[i] = lim;
                }
            }

            //"funcao" pra redistribuir excesso
            int redistribuir = excesso / 256;
            for(int i = 0; i < 256; i++)
                hist[i] += redistribuir;

            //calcula a cdf (funcao de distribuicao acumulada)
            int cdf[256] = {0};
            cdf[0] = hist[0];
            for(int i = 1; i < 256; i++)
            {
                cdf[i] = cdf[i - 1] + hist[i];
            }

            //aqui aplica transformação baseada na cdf
            for(int i = y_inicio; i < y_fim; i++)
            {
                for(int j = x_inicio; j < x_fim; j++)
                {
                    int valor = image->pixels[i * largura + j].value;
                    clahe->pixels[i * largura + j].value = (cdf[valor] * 255) / cdf[255];
                }  
            }
        }
    }

    return clahe;
}

// Operações para ImageRGB
ImageRGB *transpose_rgb(const ImageRGB *image)
{
    //Criando a struct nova
    ImageRGB *image_transpose = malloc(sizeof(ImageRGB));
    if(image_transpose == NULL)
    {
        printf("ERRO ao alocar trasnpose rgb!");
        exit(1);
    }

    //Atribuindo as dimensoes para a struct nova
    image_transpose->dim.largura = image->dim.altura;
    image_transpose->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    //Alocando os pixels
    image_transpose->pixels = malloc(image_transpose->dim.altura * image_transpose->dim.largura * sizeof(PixelRGB));
    if(image_transpose->pixels == NULL)
    {
        printf("ERRO ao alocar pixels transpose rgb!");
        free(image_transpose);
        exit(1);
    }

    //Trocando as linhas pelas colunas
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
ImageRGB *flip_horizontal_rgb(const ImageRGB *image)
{
    //Criando struct nova
    ImageRGB *image_horizontal = malloc(sizeof(ImageRGB));
    if(image_horizontal == NULL)
    {
        printf("ERRO ao alocar flip horizontal rgb!");
        exit(1);
    }

    //Atribuindo as dimensoes para a struct nova
    image_horizontal->dim.largura = image->dim.altura;
    image_horizontal->dim.altura = image->dim.largura;
    //printf("Dimensoes: %d %d", image_transpose->dim.largura, image_transpose->dim.altura);

    //Alocando os pixels
    image_horizontal->pixels = malloc(image_horizontal->dim.altura * image_horizontal->dim.largura * sizeof(PixelRGB));
    if(image_horizontal->pixels == NULL)
    {
        printf("ERRO ao alocar pixels flip horizontal rgb!");
        free(image_horizontal);
        exit(1);
    }

    for (int i = 0; i < image_horizontal->dim.altura; i++)
    {
        for (int j = 0; j < image_horizontal->dim.largura; j++)
        {
            image_horizontal->pixels[i * image_horizontal->dim.largura + j] = image->pixels[i * image->dim.largura + (image->dim.largura - j - 1)];
            //printf("%d %d %d ", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
        }
    }
    
    return image_horizontal;
}
ImageRGB *flip_vertical_rgb(const ImageRGB *image)
{
    ImageRGB *flip_image = malloc(sizeof(ImageRGB));
    if(flip_image == NULL){
        printf("erro ao alocar");
        exit(1);
    }

    flip_image->dim.altura = image->dim.altura;
    flip_image->dim.largura = image->dim.largura;
    flip_image->pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelRGB));
    if(flip_image->pixels == NULL){
        printf("erro ao alocar rgb");
        free(flip_image);
        exit(1);
    }
    for(int i = 0; i < image->dim.altura; i++)
    {
        for(int j = 0; j < image->dim.largura; j++)
        {
            flip_image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j];
        }
    }
    return flip_image;
}
