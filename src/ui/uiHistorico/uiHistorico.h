
#include <imgStruct.h>

typedef struct imgHistoricoRGB
{
  ImageRGB *imgRGB;
  struct imgHistoricoRGB *prev;
  struct imgHistoricoRGB *next;
} ImgHistoricoRGB;

typedef struct imgHistoricoGray
{
  ImageGray *imgGray;
  struct imgHistoricoGray *prev;
  struct imgHistoricoGray *next;
} ImgHistoricoGray;

extern ImgHistoricoRGB *historicoRGBInicio;
extern ImgHistoricoRGB *historicoRGBAtual;
extern ImgHistoricoGray *historicoGrayInicio;
extern ImgHistoricoGray *historicoGrayAtual;

void iniciarHistoricoRGB();
void removerValoresAFrenteRGB();
void adicionarHistoricoRGB(ImageRGB *newImgRGB);
void SeguirHistoricoRGB();
void VoltarHistoricoRGB();
void removerHistoricoRGB();

void iniciarHistoricoGray();
void removerValoresAFrenteGray();
void adicionarHistoricoGray(ImageGray *newImgGray);
void SeguirHistoricoGray();
void VoltarHistoricoGray();
void removerHistoricoGray();

