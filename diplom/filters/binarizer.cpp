#include "binarizer.h"

Binarizer::Binarizer()
{

}

void Binarizer::doBinary(QImage *image, int treshold)
{
    for(int w = 0 ; w < image->width() ; w++ ){
        for (int h = 0 ; h < image->height(); h ++){
            if(image->pixelColor(w,h).blue()>treshold){
                image->setPixelColor(w,h,QColor(imagePixel,imagePixel,imagePixel,255));
            }else{
                image->setPixelColor(w,h,QColor(noImagePixel,noImagePixel,noImagePixel,255));
            }
        }
    }
}
