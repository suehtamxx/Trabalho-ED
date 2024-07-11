#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
            printf("erro na leitura do pixel gray\n");
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
            printf("ERRO na leitura do pixel rgb\n");
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
void adicionar_rgb(LinkedRGB *l, ImageRGB *image, char *nome)
{
    Listargb *novo = malloc(sizeof(Listargb));
    if(novo == NULL){
        printf("erro ao alocar!");
        exit(1);
    }
    novo->image = image;
    novo->prox = NULL;
    novo->ant = l->corpo;
    novo->nome = strdup(nome);

    if(l->corpo != NULL){
        l->corpo->prox = novo;
    } else {
        l->cabeca = novo;
    }
    l->corpo = novo;
    l->current = novo;
}
ImageRGB *desfazer_rgb(LinkedRGB *l) 
{
    if (l == NULL || l->current == NULL)
        return NULL;

    // Salva a imagem a ser desfeita
    ImageRGB *img = l->current->image;

    // Remove o nó atual da lista
    Listargb *tmp = l->current;
    l->current = l->current->ant;

    if (l->current != NULL) {
        l->current->prox = NULL;
    } else {
        l->cabeca = NULL;  // Se l->current era o único elemento
    }

    free(tmp->nome);
    free(tmp);

    return img;
}

ImageRGB *refazer_rgb(LinkedRGB *l)
{
    if (l->corpo == NULL || l->corpo->prox == NULL) 
    {
        printf("Nenhuma operacao para refazer!\n");
        return NULL;
    }

    l->corpo = l->corpo->prox;
    return l->corpo->image;
}
void mostrar_rgb(LinkedRGB *l) 
{
    if (l == NULL) printf("Lista vazia ");
    else
    {
        Listargb *current = l->cabeca;

        while (current != NULL) 
        {
            printf("%s -> ", current->nome);
            current = current->prox;
        }
    }
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
void adicionar_gray(LinkedGray *l, ImageGray *image, char *nome)
{
    Listagray *novo = malloc(sizeof(Listagray));
    if(novo == NULL){
        printf("erro ao alocar!");
        exit(1);
    }
    novo->image = image;
    novo->prox = NULL;
    novo->ant = l->corpo;
    novo->nome = strdup(nome);

    if(l->corpo != NULL){
        l->corpo->prox = novo;
    } else {
        l->cabeca = novo;
    }
    l->corpo = novo;
}
ImageGray *desfazer_gray(LinkedGray *l) 
{
    if (l->corpo == NULL) return NULL;

    ImageGray *img = l->corpo->image;
    Listagray *tmp = l->corpo;

    l->corpo = l->corpo->ant;
    if (l->corpo != NULL) l->corpo->prox = NULL;
    else l->cabeca = NULL;
    
    free(tmp->nome);
    free(tmp);
    return img;
}
ImageGray *refazer_gray(LinkedGray *l)
{
    if(l->current == NULL || l->current->prox == NULL)
    {
        printf("Nenhuma operacao!");
        return NULL;
    }
    l->current = l->current->prox;
    return l->current->image;
}
void mostrar_gray(LinkedGray *l) 
{
    if (l == NULL) printf("Lista vazia ");
    else
    {
        Listagray *current = l->cabeca;

        while (current != NULL) 
        {
            printf("%s -> ", current->nome);
            current = current->prox;
        }
    }
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

ListRandomGray *create_list_random_gray()
{
    return NULL;
}
void add_list_random_gray(ListRandomGray **l, ImageGray *image, char *nome)
{
    if (*l == NULL)
    {
        //se o proximo elemento da lista for nulo, cria um novo elemento 
        ListRandomGray *novo = (ListRandomGray*)malloc(sizeof(ListRandomGray));
        if (novo == NULL) 
        {
            printf("ERRO ao alocar no da lista gray\n");
            exit(1);
        }

        //atribui nulo para o novo elemento, representando que é o fim da lista
        novo->prox = NULL;
        novo->image = image;
        novo->nome = strdup(nome);

        //insere no fim da lista
        *l = novo;
        
    }
    else add_list_random_gray(&((*l)->prox), image, nome);
}
void print_list_random_gray(ListRandomGray *l)
{
    if (l == NULL) printf("Lista vazia ");
    else
    {
        ListRandomGray *aux = l;
        while (aux != NULL)
        {
            printf("%s -> ", aux->nome);
            aux = aux->prox;
        }
    }
}
void free_random_gray(ListRandomGray *l)
{
    ListRandomGray *aux = l;
    ListRandomGray *proximo;

    while (aux != NULL) {
        proximo = aux->prox;

        // Libera a memória da imagem associada
        if (aux->image != NULL) {
            free(aux->image->pixels); 
            free(aux->image);         
        }

        free(aux->nome);
        free(aux);       
        aux = proximo;      
    }
}

ListRandomRGB *create_list_random_RGB()
{
    return NULL;
}
void add_list_random_rgb(ListRandomRGB **l, ImageRGB *image, char *nome)
{
    if (*l == NULL)
    {
        //se o proximo elemento da lista for nulo, cria um novo elemento 
        ListRandomRGB *novo = (ListRandomRGB*)malloc(sizeof(ListRandomRGB));
        if (novo == NULL) 
        {
            printf("ERRO ao alocar no da lista gray\n");
            exit(1);
        }

        //atribui nulo para o novo elemento, representando que é o fim da lista
        novo->prox = NULL;
        novo->image = image;
        novo->nome = strdup(nome);

        //insere no fim da lista
        *l = novo;
        
    }
    else add_list_random_rgb(&((*l)->prox), image, nome);
}
void print_list_random_rgb(ListRandomRGB *l)
{
    if (l == NULL) printf("Lista vazia ");
    else
    {
        ListRandomRGB *aux = l;
        while (aux != NULL)
        {
            printf("%s -> ", aux->nome);
            aux = aux->prox;
        }
    }
}
void free_random_rgb(ListRandomRGB *l)
{
    ListRandomRGB *aux = l;
    ListRandomRGB *proximo;

    while (aux != NULL) 
    {
        proximo = aux->prox;

        // Libera a memória da imagem associada
        if (aux->image != NULL) {
            free(aux->image->pixels); 
            free(aux->image);         
        }

        free(aux->nome);
        free(aux);       
        aux = proximo;      
    }
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
void convertGraytxt(ImageGray *image, int *numAlteracoes, char *nome, LinkedGray *l)
{
    //Criando nome do arquivo
    char nomeArq[25];
    sprintf(nomeArq, "../%sGray%d.txt", nome, *numAlteracoes);
    //printf("%d", *numAlteracoes);

    //Criando o arquivo
    FILE *arqGray;
    arqGray = fopen(nomeArq, "w");
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
    adicionar_gray(l, image, nomeArq);
}
void convertRGBtxt(ImageRGB *image, int *numAlteracoes, char *nome, LinkedRGB *l)
{
    //Criando nome do arquivo
    char nomeArq[25];
    sprintf(nomeArq, "../%sRGB%d.txt", nome, *numAlteracoes);
    //printf("%d", *numAlteracoes);

    //Criando o arquivo
    FILE *arqRGB;
    arqRGB = fopen(nomeArq, "w");
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
    adicionar_rgb(l, image, nomeArq);
}

void convertGrayRandomtxt(ImageGray *image, int *numAlteracoes, ListRandomGray **l)
{
    //Criando nome do arquivo
    char nomeArq[30];
    sprintf(nomeArq, "../GrayRandom%d.txt", *numAlteracoes);
    //printf("%d", *numAlteracoes);

    //Criando o arquivo
    FILE *arqGray;
    arqGray = fopen(nomeArq, "w");
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
    add_list_random_gray(l, image, nomeArq);
}
void convertRGBRandomtxt(ImageRGB *image, int *numAlteracoes, ListRandomRGB **l)
{
    //Criando nome do arquivo
    char NomeArq[25];
    sprintf(NomeArq, "../RGBRandom%d.txt", *numAlteracoes);
    //printf("%d", *numAlteracoes);

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
    add_list_random_rgb(l, image, NomeArq);
}

void insertion_sort(unsigned char *vet, int cont) 
{
    for (int i = 1; i < cont; i++) 
    {
        unsigned char key = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > key) 
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = key;
    }
}

// Operações para ImageGray
ImageGray *transpose_gray(const ImageGray *image)
{
    //Criando struct nova
    ImageGray *image_transpose = create_image_gray(image->dim.altura, image->dim.largura);

    //Trocando as linhas pelas colunas
    for(int i = 0; i < image->dim.altura; i++)
    {
        for(int j = 0; j < image->dim.largura; j++)
        {
            image_transpose->pixels[j * image_transpose->dim.largura + i] = image->pixels[i * image->dim.largura + j];
            //printf("%d ", image_transpose->pixels[i * image->dim.largura + j].value);
        }    
    }

    return image_transpose;
}
ImageGray *flip_horizontal_gray(ImageGray *image)
{
    //Criando struct nova
    ImageGray *image_horizontal = create_image_gray(image->dim.largura, image->dim.altura);

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
    ImageGray *flip_image = create_image_gray(image->dim.largura, image->dim.altura);

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

    ImageGray *clahe = create_image_gray(image->dim.largura, image->dim.altura);

    int n_tilesx = (largura + tile_width - 1) / tile_width;
    int n_tilesy = (altura + tile_height - 1) / tile_height;
    int lim = (tile_width * tile_height) / 8;

    //Armazenando as cdfs de cada bloco
    int (*cdf)[n_tilesx][256] = malloc(n_tilesy * n_tilesx * 256 * sizeof(int));
    if (cdf == NULL) {
        printf("Erro ao alocar memoria para o cdf.\n");
        free(clahe->pixels);
        free(clahe);
        exit(1);
    }

    memset(cdf, 0, n_tilesy * n_tilesx * 256 * sizeof(int));

    for (int iy = 0; iy < n_tilesy; iy++) 
    {
        for (int jx = 0; jx < n_tilesx; jx++) 
        {
            int x_inicio = jx * tile_width;
            int y_inicio = iy * tile_height;
            int x_fim = (x_inicio + tile_width > largura) ? largura : x_inicio + tile_width;
            int y_fim = (y_inicio + tile_height > altura) ? altura : y_inicio + tile_height;

            int hist[256] = {0};

            for (int i = y_inicio; i < y_fim; i++) 
            {
                for (int j = x_inicio; j < x_fim; j++) 
                    hist[image->pixels[i * largura + j].value]++;
            }

            int excesso = 0;
            for (int i = 0; i < 256; i++) 
            {
                if (hist[i] > lim) 
                {
                    excesso += hist[i] - lim;
                    hist[i] = lim;
                }
            }

            int redistribuir = excesso / 256;
            for (int i = 0; i < 256; i++)
                hist[i] += redistribuir;

            cdf[iy][jx][0] = hist[0];
            for (int i = 1; i < 256; i++) 
                cdf[iy][jx][i] = cdf[iy][jx][i - 1] + hist[i];
        }
    }

    // Aplicação da transformação CLAHE com interpolação bilinear
    for (int i = 0; i < altura; i++) 
    {
        for (int j = 0; j < largura; j++) 
        {
            int tile_x = j / tile_width;
            int tile_y = i / tile_height;

            int proximo_tile_x = (tile_x + 1 < n_tilesx) ? tile_x + 1 : tile_x;
            int proximo_tile_y = (tile_y + 1 < n_tilesy) ? tile_y + 1 : tile_y;

            float dx = (float)(j % tile_width) / tile_width;
            float dy = (float)(i % tile_height) / tile_height;

            unsigned char value = image->pixels[i * largura + j].value;

            int cdf_tl = cdf[tile_y][tile_x][value];
            int cdf_tr = cdf[tile_y][proximo_tile_x][value];
            int cdf_bl = cdf[proximo_tile_y][tile_x][value];
            int cdf_br = cdf[proximo_tile_y][proximo_tile_x][value];

            float cdf_top = (1 - dx) * cdf_tl + dx * cdf_tr;
            float cdf_bottom = (1 - dx) * cdf_bl + dx * cdf_br;

            float final_cdf = (1 - dy) * cdf_top + dy * cdf_bottom;

            clahe->pixels[i * largura + j].value = (final_cdf * 255) / cdf[tile_y][tile_x][255];
        }
    }

    free(cdf);
    return clahe;
}
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size)
{
    ImageGray *image_median = create_image_gray(image->dim.largura, image->dim.altura);
    
    int offset = kernel_size / 2;
    int window_size = kernel_size * kernel_size;

    unsigned char *window_gray = malloc(window_size * sizeof(unsigned char));

    if(window_gray == NULL)
    {
        printf("ERRO ao alocar janelas median blur gray");
        free(image_median->pixels);
        free(image_median);
        exit(1);
    }

    for(int i = 0; i < image_median->dim.altura; i++)
    {
        for(int j = 0; j < image_median->dim.largura; j++)
        {
            int cont = 0;

            for(int m = -offset; m <= offset; m++)
            {
                for(int n = -offset; n <= offset; n++)
                {
                    int x = j + n;
                    int y = i + m;

                    if(x >= 0 && x < image_median->dim.largura && y >= 0 && y < image_median->dim.altura)
                    {
                        PixelGray pixel = image->pixels[y * image_median->dim.largura + x];
                        window_gray[cont] = pixel.value;
                        cont++;
                    }
                }
            }

            insertion_sort(window_gray, cont);

            image_median->pixels[i * image_median->dim.largura + j].value = window_gray[cont / 2];
        }
    }
    free(window_gray);

    return image_median;
}
ImageGray *random_gray(ImageGray *image)
{
    //Criando struct nova
    ImageGray *image_random = create_image_gray(image->dim.largura, image->dim.altura);
    
    srand(time(NULL)); 
    int num = rand() % 5;
        
    switch (num)
    {
    case 0:
        image_random = transpose_gray(image);
        break;

    case 1:
        image_random = flip_horizontal_gray(image);
        break;

    case 2:
        image_random = flip_vertical_gray(image);
        break;

    case 3:
        image_random = clahe_gray(image, image->dim.largura, image->dim.altura);
        break;

    case 4:
        image_random = median_blur_gray(image, 5);
        break;
    
    default:
        break;
    }
    
    return image_random;
}

// Operações para ImageRGB
ImageRGB *transpose_rgb(const ImageRGB *image)
{
    //Criando a struct nova
    ImageRGB *image_transpose = create_image_rgb(image->dim.altura, image->dim.largura);

    //Trocando as linhas pelas colunas
    for(int i = 0; i < image->dim.altura; i++)
    {
        for(int j = 0; j < image->dim.largura; j++)
        {
            image_transpose->pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
            //printf("%d %d %d ", image->pixels[i * image->dim.largura + j].red, image->pixels[i * image->dim.largura + j].green, image->pixels[i * image->dim.largura + j].blue);
        }    
    }

    return image_transpose;
}
ImageRGB *flip_horizontal_rgb(const ImageRGB *image)
{
    //Criando struct nova
    ImageRGB *image_horizontal = create_image_rgb(image->dim.largura, image->dim.altura);

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
    ImageRGB *flip_image = create_image_rgb(image->dim.largura, image->dim.altura);
    
    for(int i = 0; i < image->dim.altura; i++)
    {
        for(int j = 0; j < image->dim.largura; j++)
            flip_image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j];
    }

    return flip_image;
}
ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height)
{
    int largura = image->dim.largura;
    int altura = image->dim.altura;

    //Criando nova struct
    ImageRGB *clahe = create_image_rgb(image->dim.largura, image->dim.altura);

    //"funcao" para definir o limite
    int n_tilesx = (largura + tile_width - 1) / tile_width;
    int n_tilesy = (altura + tile_height - 1) / tile_height;
    int lim = (tile_width * tile_height) / 8;

    //Armazenando as cdfs de cada bloco para cada canal de cor
    int (*cdfR)[n_tilesx][256] = malloc(n_tilesy * n_tilesx * 256 * sizeof(int));
    int (*cdfG)[n_tilesx][256] = malloc(n_tilesy * n_tilesx * 256 * sizeof(int));
    int (*cdfB)[n_tilesx][256] = malloc(n_tilesy * n_tilesx * 256 * sizeof(int));

    if (cdfR == NULL || cdfG == NULL || cdfB == NULL) {
        printf("Erro ao alocar memória para o cdf.\n");
        free(clahe->pixels);
        free(clahe);
        exit(1);
    }

    memset(cdfR, 0, n_tilesy * n_tilesx * 256 * sizeof(int));
    memset(cdfG, 0, n_tilesy * n_tilesx * 256 * sizeof(int));
    memset(cdfB, 0, n_tilesy * n_tilesx * 256 * sizeof(int));

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
            int histR[256] = {0};
            int histG[256] = {0};
            int histB[256] = {0};

            //calculo do histograma para o bloco atual
            for(int i = y_inicio; i < y_fim; i++)
            {
                for(int j = x_inicio; j < x_fim; j++)
                {
                    PixelRGB pixel = image->pixels[i * largura + j]; 
                    histR[pixel.red]++;
                    histG[pixel.green]++;
                    histB[pixel.blue]++;
                }
            }

            //"funcao" para limitar o histograma
            int excessoR = 0, excessoG = 0, excessoB = 0;
            for (int i = 0; i < 256; i++) 
            {
                if (histR[i] > lim) 
                {
                    excessoR += histR[i] - lim;
                    histR[i] = lim;
                }
                if (histG[i] > lim) 
                {
                    excessoG += histG[i] - lim;
                    histG[i] = lim;
                }
                if (histB[i] > lim) 
                {
                    excessoB += histB[i] - lim;
                    histB[i] = lim;
                }
            }

            //"funcao" pra redistribuir excesso
            int redistribuirR = excessoR / 256;
            int redistribuirG = excessoG / 256;
            int redistribuirB = excessoB / 256;
            for (int i = 0; i < 256; i++) 
            {
                histR[i] += redistribuirR;
                histG[i] += redistribuirG;
                histB[i] += redistribuirB;
            }

            //calcula a cdf (funcao de distribuicao acumulada)
            cdfR[iy][jx][0] = histR[0];
            cdfG[iy][jx][0] = histG[0];
            cdfB[iy][jx][0] = histB[0];

            for (int i = 1; i < 256; i++) 
            {
                cdfR[iy][jx][i] = cdfR[iy][jx][i - 1] + histR[i];
                cdfG[iy][jx][i] = cdfG[iy][jx][i - 1] + histG[i];
                cdfB[iy][jx][i] = cdfB[iy][jx][i - 1] + histB[i];
            }            
        }
    }

    //aplicar transformação CLAHE com interpolação bilinear
    for (int i = 0; i < altura; i++) 
    {
        for (int j = 0; j < largura; j++) 
        {
            int tile_x = j / tile_width;
            int tile_y = i / tile_height;

            int proximo_tile_x = (tile_x + 1 < n_tilesx) ? tile_x + 1 : tile_x;
            int proximo_tile_y = (tile_y + 1 < n_tilesy) ? tile_y + 1 : tile_y;

            float dx = (float)(j % tile_width) / tile_width;
            float dy = (float)(i % tile_height) / tile_height;

            PixelRGB pixel = image->pixels[i * largura + j];

            int cdf_tl_R = cdfR[tile_y][tile_x][pixel.red];
            int cdf_tr_R = cdfR[tile_y][proximo_tile_x][pixel.red];
            int cdf_bl_R = cdfR[proximo_tile_y][tile_x][pixel.red];
            int cdf_br_R = cdfR[proximo_tile_y][proximo_tile_x][pixel.red];

            int cdf_tl_G = cdfG[tile_y][tile_x][pixel.green];
            int cdf_tr_G = cdfG[tile_y][proximo_tile_x][pixel.green];
            int cdf_bl_G = cdfG[proximo_tile_y][tile_x][pixel.green];
            int cdf_br_G = cdfG[proximo_tile_y][proximo_tile_x][pixel.green];

            int cdf_tl_B = cdfB[tile_y][tile_x][pixel.blue];
            int cdf_tr_B = cdfB[tile_y][proximo_tile_x][pixel.blue];
            int cdf_bl_B = cdfB[proximo_tile_y][tile_x][pixel.blue];
            int cdf_br_B = cdfB[proximo_tile_y][proximo_tile_x][pixel.blue];

            float cdf_top_R = (1 - dx) * cdf_tl_R + dx * cdf_tr_R;
            float cdf_bottom_R = (1 - dx) * cdf_bl_R + dx * cdf_br_R;
            float final_cdf_R = (1 - dy) * cdf_top_R + dy * cdf_bottom_R;

            float cdf_top_G = (1 - dx) * cdf_tl_G + dx * cdf_tr_G;
            float cdf_bottom_G = (1 - dx) * cdf_bl_G + dx * cdf_br_G;
            float final_cdf_G = (1 - dy) * cdf_top_G + dy * cdf_bottom_G;

            float cdf_top_B = (1 - dx) * cdf_tl_B + dx * cdf_tr_B;
            float cdf_bottom_B = (1 - dx) * cdf_bl_B + dx * cdf_br_B;
            float final_cdf_B = (1 - dy) * cdf_top_B + dy * cdf_bottom_B;

            clahe->pixels[i * largura + j].red = (final_cdf_R * 255) / cdfR[tile_y][tile_x][255];
            clahe->pixels[i * largura + j].green = (final_cdf_G * 255) / cdfG[tile_y][tile_x][255];
            clahe->pixels[i * largura + j].blue = (final_cdf_B * 255) / cdfB[tile_y][tile_x][255];
        }
    }

    free(cdfR);
    free(cdfG);
    free(cdfB);

    return clahe;
}
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size)
{
    //Criando struct nova
    ImageRGB *image_median = create_image_rgb(image->dim.largura, image->dim.altura);

    int offset = kernel_size / 2; //Determinando o intervalo de indices ao redor do pixel
    int window_size = kernel_size * kernel_size; //Calculando o total de pixels da janela
    
    //Alocanco janelas para cada cor
    unsigned char *window_r = malloc(window_size * sizeof(unsigned char));
    unsigned char *window_g = malloc(window_size * sizeof(unsigned char));
    unsigned char *window_b = malloc(window_size * sizeof(unsigned char));

    if(window_r == NULL || window_g == NULL || window_b == NULL)
    {
        printf("ERRO ao alocar janelas median blur rgb!");
        free(image_median->pixels);
        free(image_median);
        free(window_r);
        free(window_g);
        free(window_b);
        exit(1);
    }

    //Percorrendo os pixels
    for (int i = 0; i < image_median->dim.altura; i++)
    {
        for (int j = 0; j < image_median->dim.largura; j++)
        {
            int cont = 0;

            //Encontrando o centro da janela
            for (int m = -offset; m <= offset; m++)
            {
                for (int n = -offset; n <= offset; n++)
                {
                    int x = j + n;
                    int y = i + m;
                    
                    if (x >= 0 && x < image_median->dim.largura && y >= 0 && y < image_median->dim.altura)
                    {
                        PixelRGB pixel = image->pixels[y * image_median->dim.largura + x];
                        window_r[cont] = pixel.red;
                        window_g[cont] = pixel.green;
                        window_b[cont] = pixel.blue;
                        cont++;
                    }
                }
            }
            
            //Ordenando
            insertion_sort(window_r, cont);
            insertion_sort(window_g, cont);
            insertion_sort(window_b, cont);

            //Calculando a mediana e atribuindo ao pixel
            image_median->pixels[i * image_median->dim.largura + j].red = window_r[cont / 2];
            image_median->pixels[i * image_median->dim.largura + j].green = window_g[cont / 2];
            image_median->pixels[i * image_median->dim.largura + j].blue = window_b[cont / 2];
        }
    }

    free(window_r);
    free(window_g);
    free(window_b);
    
    return image_median;
}
ImageRGB *random_rgb(ImageRGB *image)
{
    //Criando struct nova
    ImageRGB *image_random = create_image_rgb(image->dim.largura, image->dim.altura);
    
    srand(time(NULL)); 
    int num = rand() % 5;
    
    switch (num)
    {
    case 0:
        image_random = transpose_rgb(image);
        break;

    case 1:
        image_random = flip_horizontal_rgb(image);
        break;

    case 2:
        image_random = flip_vertical_rgb(image);
        break;

    case 3:
        image_random = clahe_rgb(image, image_random->dim.largura, image_random->dim.altura);
        break;

    case 4:
        image_random = median_blur_rgb(image, 5);
        break;
    
    default:
        break;
    }
    
    return image_random;
}

// Chamadas do python
void call_python_gray(int *numAlteracoes, char *nome) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "../%sGray%d.txt", nome, *numAlteracoes);
    sprintf(nomeImage, "../LenaGray.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s gray", nomeArq, nomeImage);
    system(command);
}
void call_python_rgb(int *numAlteracoes, char *nome) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "../%sRGB%d.txt", nome, *numAlteracoes);
    sprintf(nomeImage, "../LenaRGB.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s rgb", nomeArq, nomeImage);
    system(command);
}

void call_python_historico_gray(char *nome) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "%s", nome);
    sprintf(nomeImage, "../LenaGray.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s gray", nomeArq, nomeImage);
    system(command);
}
void call_python_historico_rgb(char *nome) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "%s", nome);
    sprintf(nomeImage, "../LenaRGB.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s rgb", nomeArq, nomeImage);
    system(command);
}

void call_python_gray_random(int *numAlteracoes) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "../GrayRandom%d.txt", *numAlteracoes);
    sprintf(nomeImage, "../LenaGrayRandom.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s gray", nomeArq, nomeImage);
    system(command);
}
void call_python_rgb_random(int *numAlteracoes) 
{
    char command[256], nomeArq[50], nomeImage[50];
    sprintf(nomeArq, "../RGBRandom%d.txt", *numAlteracoes);
    sprintf(nomeImage, "../LenaRGBRandom.png");

    snprintf(command, sizeof(command), "python3 ../image_utils.py %s %s rgb", nomeArq, nomeImage);
    system(command);
}