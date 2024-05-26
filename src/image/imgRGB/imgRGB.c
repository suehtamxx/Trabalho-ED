#include <imgRGB.h>
#include<stdio.h>
#include<stdlib.h>

ImageRGB *create_image_rgb(int largura, int altura){
    ImageRGB *image=(ImageRGB*)malloc(sizeof(ImageRGB));
    if(image==NULL){
        return NULL;
    }
    image->dim.largura=largura;
    image->dim.altura=altura;

    image->pixels=(PixelRGB*)malloc(largura*altura*sizeof(PixelRGB));
    if(image->pixels==NULL){
        free(image);
        return NULL;
    }
    return image;
}

void free_image_rgb(ImageRGB *image){
    if(image==NULL){
        return;
    }
    else if(image->pixels !=NULL){
        free(image->pixels);
    }

    free(image) ;
}
