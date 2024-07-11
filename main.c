#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ImageGray *menuImageGray(ImageGray *image, int *numAlteracoes, LinkedGray *l)
{
    int op = 0;

    do
    {
        printf("\n===MENU IMAGEM GRAY===\n");
        printf("1 - Transpose\n");
        printf("2 - Flip Horizontal\n");
        printf("3 - Flip Vertical\n");
        printf("4 - Clahe\n");
        printf("5 - Median blur\n");
        printf("6 - Aleatoria\n");
        printf("7 - Desfazer\n");
        printf("8 - Refazer\n");
        printf("9 - Historico\n");
        printf("10 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            image = transpose_gray(image);
            convertGraytxt(image, numAlteracoes, "Transpose-", l);
            call_python_gray(numAlteracoes, "Transpose-");
            (*numAlteracoes)++;
            break;
        
        case 2:
            image = flip_horizontal_gray(image);
            convertGraytxt(image, numAlteracoes, "FlipHorizontal-", l);
            call_python_gray(numAlteracoes, "FlipHorizontal-");
            (*numAlteracoes)++;
            break;
        
        case 3:
            image = flip_vertical_gray(image);
            convertGraytxt(image, numAlteracoes, "FlipVertical-", l);
            call_python_gray(numAlteracoes, "FlipVertical-");
            (*numAlteracoes)++;
            break;

        case 4:
            image = clahe_gray(image, image->dim.largura, image->dim.altura);
            convertGraytxt(image, numAlteracoes, "Clahe-", l);
            call_python_gray(numAlteracoes, "Clahe-");
            (*numAlteracoes)++;
            break;

        case 5:
            image = median_blur_gray(image, 5);
            convertGraytxt(image, numAlteracoes, "MedianBlur-", l);
            call_python_gray(numAlteracoes, "MedianBlur-");
            (*numAlteracoes)++;
            break;

        case 6:
            image = random_gray(image);
            convertGraytxt(image, numAlteracoes, "Random-", l);
            call_python_gray(numAlteracoes, "Random-");
            (*numAlteracoes)++;
            break;

        case 7:
                printf("Chamando desfazer_gray...\n");
                char* nomeGrayDesfeita = desfazer_gray(l);
                if (nomeGrayDesfeita != NULL) {
                    call_python_historico_gray(nomeGrayDesfeita);
                }
                break;
        case 8:
            char* nomeGrayRefeita = refazer_gray(l);
            if (nomeGrayRefeita != NULL) {
                call_python_historico_gray(nomeGrayRefeita);
            }
            break;

        case 9:
            mostrar_gray(l);
            break;

        case 10:
            printf("Voltando...\n\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 10);

    return image;
    }
ImageRGB *menuImageRGB(ImageRGB *image, int *numAlteracoes, LinkedRGB *l)
{
    int op = 0;

    do
    {
        printf("\n===MENU IMAGEM RGB===\n");
        printf("1 - Transpose\n");
        printf("2 - Flip Horizontal\n");
        printf("3 - Flip Vertical\n");
        printf("4 - Clahe\n");
        printf("5 - Median blur\n");
        printf("6 - ALeatoria\n");
        printf("7 - Desfazer\n");
        printf("8 - Refazer\n");
        printf("9 - Historico\n");
        printf("10 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            image = transpose_rgb(image);
            convertRGBtxt(image, numAlteracoes, "Transpose-", l);
            call_python_rgb(numAlteracoes, "Transpose-");
            (*numAlteracoes)++;
            break;
        
        case 2:
            image = flip_horizontal_rgb(image);
            convertRGBtxt(image, numAlteracoes, "FlipHorizontal-", l);
            call_python_rgb(numAlteracoes, "FlipHorizontal-");
            (*numAlteracoes)++;
            break;
        
        case 3:
            image = flip_vertical_rgb(image);
            convertRGBtxt(image, numAlteracoes, "FlipVertical-", l);
            call_python_rgb(numAlteracoes, "FlipVertical-");
            (*numAlteracoes)++;
            break;

        case 4:
            image = clahe_rgb(image, image->dim.largura, image->dim.altura);
            convertRGBtxt(image, numAlteracoes, "Clahe-", l);
            call_python_rgb(numAlteracoes, "Clahe-");
            (*numAlteracoes)++;
            break;

        case 5:
            image = median_blur_rgb(image, 5);
            convertRGBtxt(image, numAlteracoes, "MedianBlur-", l);
            call_python_rgb(numAlteracoes, "MedianBlur-");
            (*numAlteracoes)++;
            break;

        case 6:
            image = random_rgb(image);
            convertRGBtxt(image, numAlteracoes, "Random-", l);
            call_python_rgb(numAlteracoes, "Random-");
            (*numAlteracoes)++;
            break;

        case 7:
                
                char* nomeRGBDesfeita = desfazer_rgb(l);
                if (nomeRGBDesfeita != NULL) {
                    call_python_historico_rgb(nomeRGBDesfeita);
                }
                break;
        case 8:
            char* nomeRGBRefeita = refazer_rgb(l);
            if(nomeRGBRefeita != NULL) {
                call_python_historico_rgb(nomeRGBRefeita);
            }
            break;

        case 9:
            mostrar_rgb(l);
            break;

        case 10:
            printf("Voltando...\n\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 10);

    return image;
}

ImageGray *menuRandomGray(ImageGray *image, int *numAlteracoes, ListRandomGray **l)
{
    int op;
    do
    {
        printf("\n===MENU ALEATORIO GRAY===\n");
        printf("1 - Aplicar operacao aleatoria\n");
        printf("2 - Historico\n");
        printf("3 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op); 

        switch (op)
        {
        case 1:
            image = random_gray(image);
            convertGrayRandomtxt(image, numAlteracoes, l);
            call_python_gray_random(numAlteracoes);
            (*numAlteracoes)++;
            break;

        case 2:
            print_list_random_gray(*l);
            break;

        case 3:
            printf("Voltando...\n");
            break;
        
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 3);

    return image;
}
ImageRGB *menuRandomRGB(ImageRGB *image, int *numAlteracoes, ListRandomRGB **l)
{
    int op;
    do
    {
        printf("\n===MENU ALEATORIO RGB===\n");
        printf("1 - Aplicar operacao aleatoria\n");
        printf("2 - Historico\n");
        printf("3 - Voltar\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op); 

        switch (op)
        {
        case 1:
            image = random_rgb(image);
            convertRGBRandomtxt(image, numAlteracoes, l);
            call_python_rgb_random(numAlteracoes);
            (*numAlteracoes)++;
            break;

        case 2:
            print_list_random_rgb(*l);
            break;

        case 3:
            printf("Voltando...\n");
            break;
        
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 3);

    return image;
}

int main()
{
    int larguraGray, alturaGray, larguraRGB, alturaRGB, op = 0;
    int numAlteracoesGray = 1, numAlteracoesRGB = 1, numAlteracoesGrayRandom = 1, numAlteracoesRGBRandom = 1;

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

    //Copiando para as structs aleatorias
    ImageGray *RandomGray = create_image_gray(larguraGray, alturaGray);
    ImageRGB *RandomRGB = create_image_rgb(larguraRGB, alturaRGB);

    for (int i = 0; i < larguraGray * alturaGray; i++) 
        RandomGray->pixels[i].value = imageGray->pixels[i].value;
    
    
    for (int i = 0; i < larguraRGB * alturaRGB; i++) 
    {
        RandomRGB->pixels[i].red = imageRGB->pixels[i].red;
        RandomRGB->pixels[i].green = imageRGB->pixels[i].green;
        RandomRGB->pixels[i].blue = imageRGB->pixels[i].blue;
    }

    //Criando listas
    ListRandomGray *listrandomgray = create_list_random_gray();
    ListRandomRGB *listrandomrgb = create_list_random_RGB();
    LinkedGray *listgray = criar_gray();
    LinkedRGB *listrgb = criar_RGB();

    add_list_random_gray(&listrandomgray, imageGray, "LenaGrayRandom.txt");
    add_list_random_rgb(&listrandomrgb, imageRGB, "LenaRGBRandom.txt");
    adicionar_gray(listgray, imageGray, "imageGray.txt");
    adicionar_rgb(listrgb, imageRGB, "imageRGB.txt");

    //Transformando as imagens Originais
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "./imageGray.txt");
    sprintf(nomeImage, "../LenaGray.png");
    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s gray", nomeArq, nomeImage);
    system(command);

    sprintf(nomeArq, "./imageRGB.txt");
    sprintf(nomeImage, "../LenaRGB.png");
    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s rgb", nomeArq, nomeImage);
    system(command);

    do
    {
        printf("\n===MENU PRINCIPAL===\n");
        printf("1 - Imagem Gray\n");
        printf("2 - Imagem RGB\n");
        printf("3 - Imagem Aleatoria Gray\n");
        printf("4 - Imagem Aleatoria RGB\n");
        printf("5 - Sair\n");

        printf("Escolha uma opcao:\n");
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
            imageGray = menuImageGray(imageGray, &numAlteracoesGray, listgray);
            break;
        
        case 2:
            imageRGB = menuImageRGB(imageRGB, &numAlteracoesRGB, listrgb);
            break;

        case 3:
            RandomGray = menuRandomGray(RandomGray, &numAlteracoesGrayRandom, &listrandomgray);
            break;

        case 4:
            RandomRGB = menuRandomRGB(RandomRGB, &numAlteracoesRGBRandom, &listrandomrgb);
            break;

        case 5:
            printf("Saindo...\n\n");
            break;

        default:
            printf("Opcao invalida!\n\n");
            break;
        }
    } while (op != 5);
    
    free_image_gray(imageGray);
    free_image_rgb(imageRGB);
    free_image_gray(RandomGray);
    free_image_rgb(RandomRGB);

    free_random_gray(listrandomgray);
    free_random_rgb(listrandomrgb);
    liberar_gray(listgray);
    liberar_rgb(listrgb);

    return 0;
}