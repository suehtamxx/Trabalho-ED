#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    int larguraGray, alturaGray, larguraRGB, alturaRGB, numAlteracoesGray = 1, numAlteracoesRGB = 1;

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

    //imageGray = transpose_gray(imageGray);
    //adicionar_gray(listagray, imageGray);
    //convertGraytxt(imageGray, &numAlteracoesGray);
    
    // imageRGB = transpose_rgb(imageRGB);
    // adicionar_rgb(listargb, imageRGB);
    // convertRGBtxt(imageRGB, &numAlteracoesRGB);

    // imageRGB = flip_horizontal_rgb(imageRGB);
    // adicionar_rgb(listargb, imageRGB);
    // convertRGBtxt(imageRGB, &numAlteracoesRGB);

    
    // imageGray = flip_vertical_gray(imageGray);
    // adicionar_gray(listagray, imageGray);
    // convertGraytxt(imageGray, &numAlteracoesGray);

    /*
    imageRGB = flip_vertical_rgb(imageRGB);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB);
    */
   
    /* numAlteracoesRGB = 5;
    imageRGB = median_blur_rgb(imageRGB, 3);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB);

    imageRGB = median_blur_rgb(imageRGB, 3);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB);

    imageRGB = median_blur_rgb(imageRGB, 3);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB); */

    numAlteracoesGray = 5;
    imageGray = median_blur_gray(imageGray, 3);
    adicionar_gray(listagray, imageGray);
    convertGraytxt(imageGray, &numAlteracoesGray);

    /* imageRGB = median_blur_rgb(imageRGB, 3);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB);

    imageRGB = median_blur_rgb(imageRGB, 3);
    adicionar_rgb(listargb, imageRGB);
    convertRGBtxt(imageRGB, &numAlteracoesRGB);
 */
    free_image_gray(imageGray);
    free_image_rgb(imageRGB);

    return 0;
}