#include <imgRGB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ImageRGB *create_image_rgb(int largura, int altura)
{
    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (image == NULL)
    {
        return NULL;
    }
    image->dim.largura = largura;
    image->dim.altura = altura;

    image->pixels = (PixelRGB *)malloc(largura * altura * sizeof(PixelRGB));
    if (image->pixels == NULL)
    {
        free(image);
        return NULL;
    }
    return image;
}

void free_image_rgb(ImageRGB *image)
{
    if (image == NULL)
    {
        return;
    }
    else if (image->pixels != NULL)
    {
        free(image->pixels);
    }

    free(image);
}

ImageRGB *flip_vertical_rgb(const ImageRGB *image)
{
    if (image == NULL)
    {
        return NULL;
    }
    int largura = image->dim.largura;
    int altura = image->dim.altura;

    // to criando uma nova imagem e armazenando em nova_image.
    ImageRGB *nova_imageVertical = create_image_rgb(largura, altura);

    if (nova_imageVertical == NULL)
    {
        return NULL;
    }
    // aqui ira copiar os pixels da imagem original para a nova imagem e inverter ela verticalmente.
    for (int i = 0; i < altura; ++i)
    {
        for (int x = 0; x < largura; ++x)
        {
            nova_imageVertical->pixels[(altura - 1 - i) * largura + x] = image->pixels[i * largura + x];
        }
    }
    return nova_imageVertical;
}

ImageRGB *flip_horizontal_rgb(const ImageRGB *image)
{
    if (image == NULL)
    {
        return NULL;
    }

    int largura = image->dim.largura;
    int altura = image->dim.altura;

    ImageRGB *nova_imagem_horizontal = create_image_rgb(largura, altura);

    if (nova_imagem_horizontal == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < altura; ++i)
    {
        for (int y = 0; y < largura; ++y)
        {
            nova_imagem_horizontal->pixels[i * largura + (largura - 1 - y)] = image->pixels[i * largura + y];
        }
    }
    return nova_imagem_horizontal;
}

ImageRGB *transpose_rgb(const ImageRGB *image)
{
    ImageRGB *newImg = image;
    return newImg;
}

ImageRGB *add90_rotation_RGB(const ImageRGB *image)
{
    ImageRGB *newImg = image;
    return newImg;
}

ImageRGB *neq90_rotation_RGB(const ImageRGB *image)
{
    ImageRGB *newImg = image;
    return newImg;
}

ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height)
{
    ImageRGB *newImg = image;
    return newImg;
}

ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size)
{
    ImageRGB *newImg = image;
    return newImg;
}

ImageRGB *read_imageRGB(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        char *suf = "builddir/";
        char *new_filename = malloc(strlen(filename) + strlen(suf) + 1);
        strcpy(new_filename, suf);
        strcat(new_filename, filename);
        file = fopen(new_filename, "r");
        if (!file)
        {
            fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
            return NULL;
        }
        free(new_filename);
    }

    int largura, altura;

    fscanf(file, "%d %d", &largura, &altura);

    ImageRGB *image = create_image_rgb(largura, altura);
    image->dim.altura = altura;
    image->dim.largura = largura;

    if (image == NULL)
    {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < largura * altura; i++)
    {
        fscanf(file, "%d %d %d", &image->pixels[i].red, &image->pixels[i].green, &image->pixels[i].blue);
        fgetc(file);
    }

    fclose(file);
    return image;
}

void mostra_imageRGB(const ImageRGB *image)
{
    if (image == NULL)
    {
        printf("imagem é NULL");
        return;
    }

    int largura = image->dim.largura;
    int altura = image->dim.altura;

    for (int i = 0; i < altura; ++i)
    {
        for (int y = 0; y < largura; ++y)
        {
            PixelRGB pixel = image->pixels[i * largura + y];
            printf("(%d,%d,%d)", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }
}

ImageRGB *transpose_rgb(const ImageRGB *image){
    if(image==NULL){
        return NULL;

    }
    int largura=image->dim.largura;
    int altura=image->dim.altura;

    ImageRGB*transpose_image=create_image_rgb(altura,largura);

    if(transpose_image==NULL){
        return NULL;
    }

    for(int i=0;i<altura;++i){
        for(int y=0;y<largura;++y){
            transpose_image->pixels[y*altura+i]=image->pixels[i*largura+y];
        }
    }
    return  transpose_image;
}
