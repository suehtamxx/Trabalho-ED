#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int larguraGray, alturaGray, larguraRGB, alturaRGB;

    LinkedRGB *listargb = criar_RGB();
    LinkedGray *listagray = criar_gray();
    //Criando arquivo
    FILE *arqGray;
    arqGray = fopen("imageGray.txt", "r");
    FILE *arqRGB;
    arqRGB = fopen("imageRGB.txt", "r");
    if (arqGray == NULL || arqRGB == NULL)
    {
        printf("ERRO ao abrir os arquivos!\n");
        fclose(arqGray);
        fclose(arqRGB);
        exit(1);
    }

    //Lendo dimensoes
    if (fscanf(arqGray,"%d %d", &larguraGray, &alturaGray) !=2)
    {
        printf("ERRO na leitura da dimensao gray");
        fclose(arqGray);
        exit(1);
    }
    if (fscanf(arqRGB,"%d %d", &larguraRGB, &alturaRGB) !=2)
    {
        printf("ERRO na leitura da dimensao rgb");
        fclose(arqRGB);
        exit(1);
    }

    //Criando struct
    ImageGray *imageGray = create_image_gray(larguraGray, alturaGray);
    ImageRGB *imageRGB = create_image_rgb(larguraRGB, alturaRGB);
    if (imageGray == NULL || imageRGB == NULL)
    {
        printf("ERRO ao alocar!\n");
        exit(1);
    }
    
    readFileGray(imageGray, arqGray);
    readFileRGB(imageRGB, arqRGB);

    fclose(arqGray);
    fclose(arqRGB);

    adicionar_rgb(listargb, imageRGB);
    adicionar_gray(listagray, imageGray);

    imageGray = transpose_gray(imageGray);
    adicionar_gray(listagray, transpose_gray);
    convertGraytxt(imageGray);
    
    imageRGB = transpose_rgb(imageRGB);
    adicionar_rgb(listargb, transpose_rgb);
    convertRGBtxt(imageRGB);

    free_image_gray(imageGray);
    free_image_rgb(imageRGB);

    return 0;
}