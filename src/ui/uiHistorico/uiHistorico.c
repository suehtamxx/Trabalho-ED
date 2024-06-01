#include <uiHistorico.h>
#include <imgRGB.h>
#include <imgGray.h>
#include <gtk/gtk.h>

ImgHistoricoRGB *historicoRGBInicio = NULL;
ImgHistoricoRGB *historicoRGBAtual = NULL;
ImgHistoricoGray *historicoGrayInicio = NULL;
ImgHistoricoGray *historicoGrayAtual = NULL;

void iniciarHistoricoRGB()
{
  historicoRGBInicio = (ImgHistoricoRGB *)malloc(sizeof(ImgHistoricoRGB));
  if (historicoRGBInicio == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para o histórico inicial.\n");
    return;
  }
  historicoRGBInicio->imgRGB = read_imageRGB("imgRGB.txt");
  if (historicoRGBInicio->imgRGB == NULL)
  {
    fprintf(stderr, "Erro ao ler a imagem inicial do arquivo.\n");
    free(historicoRGBInicio);
    historicoRGBInicio = NULL;
    return;
  }

  historicoRGBInicio->buttonStatus.flip_horizontal = 0;
  historicoRGBInicio->buttonStatus.flip_vertical = 0;
  historicoRGBInicio->buttonStatus.transpose = 0;
  historicoRGBInicio->buttonStatus.clahe = 0;
  historicoRGBInicio->buttonStatus.median_blur = 0;

  historicoRGBInicio->prev = NULL;
  historicoRGBInicio->next = NULL;
  historicoRGBAtual = historicoRGBInicio;
}

void removerValoresAFrenteRGB()
{
  if (historicoRGBAtual == NULL || historicoRGBAtual->next == NULL)
    return;

  ImgHistoricoRGB *aux = historicoRGBAtual->next;
  while (aux != NULL)
  {
    ImgHistoricoRGB *temp = aux;
    aux = aux->next;
    free(temp->imgRGB);
    free(temp);
  }
  historicoRGBAtual->next = NULL;
}

void adicionarHistoricoRGB(ImageRGB *newImgRGB, FuncUsed funcUsed)
{
  ImgHistoricoRGB *novaEntrada = (ImgHistoricoRGB *)malloc(sizeof(ImgHistoricoRGB));
  if (novaEntrada == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para nova entrada do histórico.\n");
    return;
  }

  novaEntrada->buttonStatus = historicoRGBAtual->buttonStatus;
  novaEntrada->imgRGB = newImgRGB;
  novaEntrada->prev = historicoRGBAtual;
  novaEntrada->next = NULL;

  if (funcUsed == FLIP_HORIZONTAL)
    novaEntrada->buttonStatus.flip_horizontal = !novaEntrada->buttonStatus.flip_horizontal;
  else if (funcUsed == FLIP_VERTICAL)
    novaEntrada->buttonStatus.flip_vertical = !novaEntrada->buttonStatus.flip_vertical;
  else if (funcUsed == TRANSPOSE)
    novaEntrada->buttonStatus.transpose = !novaEntrada->buttonStatus.transpose;
  else if (funcUsed == CLAHE)
    novaEntrada->buttonStatus.clahe = !novaEntrada->buttonStatus.clahe;
  else if (funcUsed == MEDIAN_BLUR)
    novaEntrada->buttonStatus.median_blur = !novaEntrada->buttonStatus.median_blur;

  if (historicoRGBInicio == NULL)
  {
    historicoRGBInicio = novaEntrada;
    historicoRGBAtual = novaEntrada;
    return;
  }

  removerValoresAFrenteRGB();
  historicoRGBAtual->next = novaEntrada;
  novaEntrada->prev = historicoRGBAtual;
  historicoRGBAtual = novaEntrada;
}

void SeguirHistoricoRGB()
{
  if (historicoRGBAtual != NULL && historicoRGBAtual->next != NULL)
    historicoRGBAtual = historicoRGBAtual->next;
}

void VoltarHistoricoRGB()
{
  if (historicoRGBAtual != NULL && historicoRGBAtual->prev != NULL)
    historicoRGBAtual = historicoRGBAtual->prev;
}

void iniciarHistoricoGray()
{
  historicoGrayInicio = (ImgHistoricoGray *)malloc(sizeof(ImgHistoricoGray));
  if (historicoGrayInicio == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para o histórico inicial.\n");
    return;
  }
  historicoGrayInicio->imgGray = read_image_gray_from_file("imgGray.txt");
  if (historicoGrayInicio->imgGray == NULL)
  {
    fprintf(stderr, "Erro ao ler a imagem inicial do arquivo.\n");
    free(historicoGrayInicio);
    historicoGrayInicio = NULL;
    return;
  }

  historicoGrayInicio->buttonStatus.flip_horizontal = 0;
  historicoGrayInicio->buttonStatus.flip_vertical = 0;
  historicoGrayInicio->buttonStatus.transpose = 0;
  historicoGrayInicio->buttonStatus.clahe = 0;
  historicoGrayInicio->buttonStatus.median_blur = 0;

  historicoGrayInicio->prev = NULL;
  historicoGrayInicio->next = NULL;
  historicoGrayAtual = historicoGrayInicio;
}

void removerValoresAFrenteGray()
{
  if (historicoGrayAtual == NULL || historicoGrayAtual->next == NULL)
    return;

  ImgHistoricoGray *aux = historicoGrayAtual->next;
  while (aux != NULL)
  {
    ImgHistoricoGray *temp = aux;
    aux = aux->next;
    free_image_gray(temp->imgGray);
    free(temp);
  }
  historicoGrayAtual->next = NULL;
}

void adicionarHistoricoGray(ImageGray *newImgGray, FuncUsed funcUsed)
{
  ImgHistoricoGray *novaEntrada = (ImgHistoricoGray *)malloc(sizeof(ImgHistoricoGray));
  if (novaEntrada == NULL)
  {
    fprintf(stderr, "Erro ao alocar memória para nova entrada do histórico.\n");
    return;
  }

  novaEntrada->buttonStatus = historicoGrayAtual->buttonStatus;
  novaEntrada->imgGray = newImgGray;
  novaEntrada->prev = historicoGrayAtual;
  novaEntrada->next = NULL;

  if (funcUsed == FLIP_HORIZONTAL)
    novaEntrada->buttonStatus.flip_horizontal = !novaEntrada->buttonStatus.flip_horizontal;
  else if (funcUsed == FLIP_VERTICAL)
    novaEntrada->buttonStatus.flip_vertical = !novaEntrada->buttonStatus.flip_vertical;
  else if (funcUsed == TRANSPOSE)
    novaEntrada->buttonStatus.transpose = !novaEntrada->buttonStatus.transpose;
  else if (funcUsed == CLAHE)
    novaEntrada->buttonStatus.clahe = !novaEntrada->buttonStatus.clahe;
  else if (funcUsed == MEDIAN_BLUR)
    novaEntrada->buttonStatus.median_blur = !novaEntrada->buttonStatus.median_blur;

  if (historicoGrayInicio == NULL)
  {
    historicoGrayInicio = novaEntrada;
    historicoGrayAtual = novaEntrada;
    return;
  }

  removerValoresAFrenteGray();
  historicoGrayAtual->next = novaEntrada;
  novaEntrada->prev = historicoGrayAtual;
  historicoGrayAtual = novaEntrada;
}

void SeguirHistoricoGray()
{
  if (historicoGrayAtual != NULL && historicoGrayAtual->next != NULL)
    historicoGrayAtual = historicoGrayAtual->next;
}

void VoltarHistoricoGray()
{
  if (historicoGrayAtual != NULL && historicoGrayAtual->prev != NULL)
    historicoGrayAtual = historicoGrayAtual->prev;
}

void removerHistoricoRGB()
{
  if (historicoRGBInicio == NULL)
    return;

  ImgHistoricoRGB *aux = historicoRGBInicio;
  while (aux != NULL)
  {
    ImgHistoricoRGB *temp = aux;
    aux = aux->next;
    free(temp->imgRGB);
    free(temp);
  }
  historicoRGBInicio = NULL;
  historicoRGBAtual = NULL;
}

void removerHistoricoGray()
{
  if (historicoGrayInicio == NULL)
    return;

  ImgHistoricoGray *aux = historicoGrayInicio;
  while (aux != NULL)
  {
    ImgHistoricoGray *temp = aux;
    aux = aux->next;
    free_image_gray(temp->imgGray);
    free(temp);
  }
  historicoGrayInicio = NULL;
  historicoGrayAtual = NULL;
}
