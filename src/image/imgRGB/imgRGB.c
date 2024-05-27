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


ImageRGB *flip_vertical_rgb(const ImageRGB *image){
    if(image==NULL){
        return NULL;
    }
    int largura=image->dim.largura;
    int altura=image->dim.altura;

    //to criando uma nova imagem e armazenando em nova_image.
    ImageRGB *nova_imageVertical=create_image_rgb(largura,altura);
    
    if(nova_imageVertical==NULL){
        return NULL;
    }
    //aqui ira copiar os pixels da imagem original para a nova imagem e inverter ela verticalmente.
    for(int i=0;i<altura;++i){
        for(int x = 0;x<largura;++x ){
            nova_image->pixels[(altura-1-i) * largura + x]=image->pixels[i*largura+x];
        }
    }
    return nova_imageVertical;
}

ImageRGB *flip_horizontal_rgb(const ImageRGB *image){
    if(image==NULL){
        return NULL;
    }

    int largura=image->dim.largura;
    int altura=image->dim.altura;


    ImageRGB *nova_imagem_horizontal=create_image_rgb(largura,altura);
    
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

