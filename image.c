#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// Funções de criação e liberação
ImageGray *create_image_gray(int largura, int altura)
{
    ImageGray *imageGray = malloc(sizeof(imageGray));

    //Alocando memoria
    
    
    return imageGray;
}

void free_image_gray(ImageGray *image)
{
    free(image);
}
