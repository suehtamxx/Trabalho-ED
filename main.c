#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void call_python_gray(int *numAlteracoes) 
// {
//     char command[256], nomeArq[25], nomeImage[25];
//     sprintf(nomeArq, "../AlteracaoGray%d.txt", *numAlteracoes);
//     sprintf(nomeImage, "../AlteracaoGray%d.png", *numAlteracoes);

//     snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s gray", nomeArq, nomeImage);
//     system(command);
// }

// void call_python_rgb(int *numAlteracoes) 
// {
//     char command[256], nomeArq[25], nomeImage[25];
//     sprintf(nomeArq, "../AlteracaoRGB%d.txt", *numAlteracoes);
//     sprintf(nomeImage, "../AlteracaoRGB%d.png", *numAlteracoes);

//     snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s rgb", nomeArq, nomeImage);
//     system(command);
// }

void menuImageGray(ImageGray *image, int numAlteracoes)
{
    //Criando lista dupla
    LinkedGray *l = criar_gray();

    int op = 0;

    do
    {
        printf("\n===MENU IMAGEM GRAY===\n");
        printf("1 - Transpose\n");
        printf("2 - Flip Horizontal\n");
        printf("3 - Flip Vertical\n");
        printf("4 - Clahe\n");
        printf("5 - Median blur\n");
        printf("6 - Desfazer\n");
        printf("7 - Refazer\n");
        printf("8 - Historico\n");
        printf("9 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            image = transpose_gray(image);
            convertGraytxt(image, &numAlteracoes);
            adicionar_gray(l, image);
            //call_python_gray(&numAlteracoes);
            break;
        
        case 2:
            image = flip_horizontal_gray(image);
            convertGraytxt(image, &numAlteracoes);
            adicionar_gray(l, image);
            //call_python_gray(&numAlteracoes);
            break;
        
        case 3:
            image = flip_vertical_gray(image);
            convertGraytxt(image, &numAlteracoes);
            adicionar_gray(l, image);
            //call_python_gray(&numAlteracoes);
            break;

        case 4:
            image = clahe_gray(image, image->dim.largura, image->dim.altura);
            convertGraytxt(image, &numAlteracoes);
            adicionar_gray(l, image);
            //call_python_gray(&numAlteracoes);
            break;

        case 5:
            image = median_blur_gray(image, 5);
            convertGraytxt(image, &numAlteracoes);
            adicionar_gray(l, image);
            //call_python_gray(&numAlteracoes);
            break;

        case 9:
            printf("Voltando...\n\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 6);
}

void menuImageRGB(ImageRGB *image, int alteracoes)
{
    //Criando lista dupla
    LinkedRGB *l = criar_RGB();

    int op = 0;

    do
    {
        printf("\n===MENU IMAGEM RGB===\n");
        printf("1 - Transpose\n");
        printf("2 - Flip Horizontal\n");
        printf("3 - Flip Vertical\n");
        printf("4 - Clahe\n");
        printf("5 - Median blur\n");
        printf("6 - Desfazer\n");
        printf("7 - Refazer\n");
        printf("8 - Historico\n");
        printf("9 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            image = transpose_rgb(image);
            convertRGBtxt(image, &alteracoes);
            adicionar_rgb(l, image);
            break;
        
        case 2:
            image = flip_horizontal_rgb(image);
            convertRGBtxt(image, &alteracoes);
            adicionar_rgb(l, image);
            break;
        
        case 3:
            image = flip_vertical_rgb(image);
            convertRGBtxt(image, &alteracoes);
            adicionar_rgb(l, image);
            break;

        case 4:
            image = clahe_rgb(image, image->dim.largura, image->dim.altura);
            convertRGBtxt(image, &alteracoes);
            adicionar_rgb(l, image);
            break;

        case 5:
            image = median_blur_rgb(image, 5);
            convertRGBtxt(image, &alteracoes);
            adicionar_rgb(l, image);
            break;

        case 9:
            printf("Voltando...\n\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 6);
}

void menuImageAteatoria()
{
    int larguraGray, alturaGray, larguraRGB, alturaRGB, op = 0;

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
        printf("ERRO ao alocar structs!\n");
        exit(1);
    }
    
    //Chamando as funcoes para ler os arquivos e colocar nas structs
    readFileGray(imageGray, arqGray);
    readFileRGB(imageRGB, arqRGB);
    
    fclose(arqGray);
    fclose(arqRGB);

    do
    {
        printf("\n===MENU ALEATORIO===\n");
        printf("1 - Criar imagem aleatoria Gray\n");
        printf("2 - Criar imagem aleatoria RGB\n");
        printf("3 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op); 

        switch (op)
        {
        case 1:
            random_gray(imageGray);
            break;

        case 2:
            random_rgb(imageRGB);
            break;

        case 3:
            printf("Voltando...\n");
            break;
        
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 3);
    
}

int main()
{
    int larguraGray, alturaGray, larguraRGB, alturaRGB, numAlteracoesGray = 1, numAlteracoesRGB = 1, op = 0;

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
        printf("ERRO ao alocar structs!\n");
        exit(1);
    }
    
    //Chamando as funcoes para ler os arquivos e colocar nas structs
    readFileGray(imageGray, arqGray);
    readFileRGB(imageRGB, arqRGB);
    
    fclose(arqGray);
    fclose(arqRGB);

    do
    {
        printf("\n===MENU PRINCIPAL===\n");
        printf("1 - Imagem Gray\n");
        printf("2 - Imagem RGB\n");
        printf("3 - Imagem Aleatoria\n");
        printf("4 - Sair\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            menuImageGray(imageGray, numAlteracoesGray);
            break;
        
        case 2:
            menuImageRGB(imageRGB, numAlteracoesRGB);
            break;

        case 3:
            menuImageAteatoria();
            break;

        case 4:
            printf("Saindo...\n\n");
            break;

        default:
            printf("Opcao invalida!\n\n");
            break;
        }
    } while (op != 3);
    
    free_image_gray(imageGray);
    free_image_rgb(imageRGB);

    return 0;
}