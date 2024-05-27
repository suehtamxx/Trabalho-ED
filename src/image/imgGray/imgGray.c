#include <imgGray.h>
#include <stdio.h>
#include <stdlib.h>

ImageGray *create_image_gray(int largura, int altura)
{
  ImageGray *img = calloc(1, sizeof(ImageGray));

  img->dim.altura = altura;
  img->dim.largura = largura;
  img->pixels = calloc((largura * altura), sizeof(PixelGray));

  return img;
}
// void free_image_gray(ImageGray *image)
// {
//   if (image)
//   {
//     free(image->pixels);
//     free(image);
//   }
// }

ImageGray *read_image_gray_from_file(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    // botar sufixo builddir no filename
    char *suf = "builddir/";
    char *new_filename = malloc(strlen(filename) + strlen(suf) + 1);
    strcpy(new_filename, suf);
    strcat(new_filename, filename);
    file = fopen(new_filename, "r");
    if(!file)
    {
      fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
      return NULL;
    }
    free(new_filename);
  }

  int largura, altura;
  fscanf(file, "%d %d", &largura, &altura);
  // Leia as dimensões da imagem

  ImageGray *image = create_image_gray(largura, altura);
  if (!image)
  {
    fclose(file);
    return NULL;
  }

  for (int i = 0; i < altura; i++)
  {
    for (int j = 0; j < largura; j++)
    {
      fscanf(file, "%d", &image->pixels[i * largura + j].value);
      fgetc(file);
    }
  }
  fclose(file);
  return image;
}

ImageGray *flip_vertical_gray(ImageGray *image){
    if(image==NULL){
        return NULL;
    }
    int largura=image->dim.largura;
    int altura=image->dim.altura;

    //to criando uma nova imagem e armazenando em nova_image.
    ImageGray *nova_imageVertical=create_image_gray(largura,altura);
    
    if(nova_imageVertical==NULL){
        return NULL;
    }
    //aqui ira copiar os pixels da imagem original para a nova imagem e inverter ela verticalmente.
    for(int i=0;i<altura;++i){
        for(int x = 0;x<largura;++x ){
            nova_imageVertical->pixels[(altura-1-i) * largura + x]=image->pixels[i*largura+x];
        }
    }
    return nova_imageVertical;
}

ImageGray *flip_horizontal_gray(ImageGray *image){
    if(image==NULL){
        return NULL;
    }

    int largura=image->dim.largura;
    int altura=image->dim.altura;


    ImageGray *nova_imagem_horizontal=create_image_gray(largura,altura);
    
    if(nova_imagem_horizontal==NULL){
        return NULL;
    }

    for(int i=0;i<altura;++i){
        for(int y=0;y<largura;++y){
            nova_imagem_horizontal->pixels[i*largura +(largura-1-y)]=image->pixels[i*largura + y];
        }
    }
    return nova_imagem_horizontal;
}

void helloWord()
{
  printf("Hello, World!\n");
}
