#include <imgGray.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (!file)
    {
      fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
      return NULL;
    }
    free(new_filename);
  }

  int largura, altura;
  fscanf(file, "%d", &altura);
  fscanf(file, "%d", &largura);
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

ImageGray *flip_vertical_gray(ImageGray *image)
{
  if (image == NULL)
  {
    return NULL;
  }
  int largura = image->dim.largura;
  int altura = image->dim.altura;

  // Criando uma nova imagem e armazenando em nova_image.
  ImageGray *nova_imageVertical = create_image_gray(largura, altura);

  if (nova_imageVertical == NULL)
  {
    return NULL;
  }
  // Aqui ira copiar os pixels da imagem original para a nova imagem e inverter ela verticalmente.
  for (int i = 0; i < altura; ++i)
  {
    for (int x = 0; x < largura; ++x)
    {
      nova_imageVertical->pixels[(altura - 1 - i) * largura + x] = image->pixels[i * largura + x];
    }
  }
  return nova_imageVertical;
}

ImageGray *flip_horizontal_gray(ImageGray *image)
{
  if (image == NULL)
  {
    return NULL;
  }

  int largura = image->dim.largura;
  int altura = image->dim.altura;

  ImageGray *nova_imagem_horizontal = create_image_gray(largura, altura);

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

ImageGray *transpose_gray(const ImageGray *image)
{

  int largura = image->dim.largura;
  int altura = image->dim.altura;

  ImageGray *imagem_trasposta = create_image_gray(largura, altura);

  if (imagem_trasposta == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < largura; i++)
  {
    for (int j = 0; j < altura; j++)
    {
      imagem_trasposta->pixels[j * altura + i].value = image->pixels[i * largura + j].value;
    }
  }
  return imagem_trasposta;
}

// calcula o histograma
void calcula_histograma(const PixelGray *regiao, int width, int *histograma)
{
  for (int i = 0; i < width; i++)
  {
    // inicializa histograma com 0
    histograma[i] = 0;
  }

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < width; j++)
    {
      int intensidade = regiao[i * width + j].value;
      histograma[intensidade]++;
    }
  }
}

void limite_Histograma(int *histograma, float limite)
{
  int excesso_pixel = 0;
  for (int i = 0; i < 256; i++)
  {
    if (histograma[i] > limite)
    {
      excesso_pixel += histograma[i] - limite;
      histograma[i] = limite;
    }
  }
  int redestribuir = excesso_pixel / 256;

  for (int i = 0; i < 256; i++)
  {
    histograma[i] = redestribuir;
  }
}

void calcula_cdf(const int *histograma, float *cdf)
{
  float total = 0;

  for (int i = 0; i < 256; i++)
  {
    total += histograma[i];
    cdf[i] = total;
  }

  for (int i = 0; i < 256; i++)
  {
    cdf[i] /= total;
  }
}

void equalizar_regiao(PixelGray *regiao, int width, int height, const float *cdf)
{
  for (int i = 0; i < width * height; i++)
  {
    int valor_pixel = regiao[i].value;
    regiao[i].value = (int)(cdf[valor_pixel] * 255);
  }
}

ImageGray *clahe_gray(const ImageGray *image)
{
  int tile_width = 32;
  int tile_height = 32;

  int largura = image->dim.largura;
  int altura = image->dim.altura;

  int numero_tiles_largura = (largura + tile_width - 1) / tile_width;
  int numero_tiles_altura = (altura + tile_height - 1) / tile_height;

  float limite_clip = 4.0;

  int limite_pixels = (int)(limite_clip * ((tile_height * tile_width) / 256));

  ImageGray *resultado = create_image_gray(largura, altura);

  int *histograma = (int *)calloc(256, sizeof(int));
  float *cdf = (float *)calloc(256, sizeof(float));

  for (int tile_y = 0; tile_y < numero_tiles_altura; tile_y++)
  {
    for (int tile_x = 0; tile_x < numero_tiles_largura; tile_x++)
    {
      int start_x = tile_x * tile_width;
      int start_y = tile_y * tile_height;
      int end_x = (tile_x + 1) * tile_width;
      int end_y = (tile_y + 1) * tile_height;

      if (end_x > largura)
        end_x = largura;
      if (end_y > altura)
        end_y = altura;

      int largura_regiao = end_x - start_x;
      int altura_regiao = end_y - start_y;

      PixelGray *regiao = (PixelGray *)calloc(largura_regiao * altura_regiao, sizeof(PixelGray));

      for (int i = 0; i < altura_regiao; i++)
      {
        for (int j = 0; j < largura_regiao; j++)
        {
          regiao[i * largura_regiao + j] = image->pixels[(start_y + i) * largura + start_x + j];
        }
      }

      calcula_histograma(regiao, largura, histograma);

      limite_Histograma(histograma, limite_pixels);

      calcula_cdf(histograma, cdf);

      equalizar_regiao(regiao, largura_regiao, altura_regiao, cdf);

      for (int k = 0; k < altura_regiao; k++)
      {
        for (int l = 0; l < largura_regiao; l++)
        {
          resultado->pixels[(start_y + k) * largura + start_x + l] = regiao[k * largura_regiao + l];
        }
      }
      free(regiao);
    }
  }

  free(histograma);
  free(cdf);

  return resultado;
}

ImageGray *median_blur_gray(const ImageGray *image)
{
  // ALTERE A NEWIMAGE PARA A IMAGEM QUE SERÁ RETORNADA
  ImageGray *newImage = image;

  // DEFINA O KERNEL_SIZE AQUI, OU ME AVISE PARA EU MUDAR DIRETO NA GUI QUANDO FOR CHAMADA
  int kernel_size = NULL;

  return newImage;
}

ImageGray *add90_rotation_gray(const ImageGray *image)
{
  ImageGray *newImage = image;

  return newImage;
}

ImageGray *neq90_rotation_gray(const ImageGray *image)
{
  ImageGray *newImage = image;

  return newImage;
}

void helloWord()
{
  printf("Hello, World!\n");
}
