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
void free_image_gray(ImageGray *image)
{
  if (image)
  {
    free(image->pixels);
    free(image);
  }
}

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
  // Leia as dimensões da imagem
  if (fscanf(file, "%d %d", &largura, &altura) != 2)
  {
    fprintf(stderr, "Falha ao ler as dimensões da imagem\n");
    fclose(file);
    return NULL;
  }

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

  return image;
}

void helloWord()
{
  printf("Hello, World!\n");
}
