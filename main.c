#include "image.h"
#include "image.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    ImageRGB *imageRGB;
    ImageGray *imageGray;
    
    imageGray = create_image_gray(0, 0);

    free_image_gray(imageGray);

    return 0;
}