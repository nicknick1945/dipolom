#ifndef UTILS_H
#define UTILS_H


#include "qimage.h"
#include "qstring.h"
#include "platform/logger/loggerfactory.h"
#include "platform/logger/logger.h"
#include "vector"
#include <diplom/filters/mysuperfilter.h>"
#include "exception"

#include <QHash>

using namespace std;

class Utils{
  public:
    Utils();
    /**
     * @brief loadImage Функция загружает изображение по заданном путю
     * @param path
     * @return
     */
    static QImage*  loadImage(QString &path){
        QImage *img  =new  QImage();

        LoggerFactory *loggerFactory = new LoggerFactory();
        Logger *logger = loggerFactory->getInstance();
        logger->debug("Путь к загружаемой фотографии:");
        logger->debug(path);
        if(img->load(path)){
            logger->info("изображение успешно загруженно ");
        }else{
            logger->error("ошибка загрузки фотографии");
        }
        return img;
    }


    static void prepareColorByCordsToImage (QImage &image, int color,QHash<int,PixelType> *pixels){
        QHashIterator<int,PixelType> iter(*pixels);
        while(iter.hasNext()){
            iter.next();
            int coordX = iter.key()%10000;
            int coordY = iter.key()/10000;
            image.setPixelColor(coordX,coordY,QColor(color,color,color,255));
        }
    }

    static bool inImage( int x, int y,QImage *image){
        return x >= 0 && x <= (image->width() - 1 ) && y >=0 && y <= (image->height() -1 );
    }

    static void doDelatation(QImage *image){
        int WHITE = 255;
        vector<vector<int>> imageArray;
        imageArray.resize(image->height());
        for(int i = 0 ; i < imageArray.size();i++){
            imageArray.at(i).resize(image->width());
        }
        for (int w = 0 ; w  < image->width() ;w ++){
            for (int h = 0 ; h < image->height(); h++){
                if(image->pixelColor(w,h).blue() == WHITE){
                   if(inImage(w-1,h-1,image)){
                       imageArray[h-1][w-1] = WHITE;
                   }
                   if(inImage(w,h-1,image)){
                      imageArray[h-1][w] = WHITE;
                   }

                   if(inImage(w+1,h-1,image)){
                      imageArray[h-1][w+1] = WHITE;
                   }

                   if(inImage(w-1,h,image)){
                       imageArray[h][w-1] = WHITE;
                   }

                   if(inImage(w,h,image)){
                      imageArray[h][w] = WHITE;
                   }

                   if(inImage(w+1,h,image)){
                       imageArray[h][w+1] = WHITE;
                   }

                   if(inImage(w-1,h+1,image)){
                       imageArray[h+1][w-1] = WHITE;
                   }

                   if(inImage(w,h+1,image)){
                       imageArray[h+1][w] = WHITE;
                   }

                   if(inImage(w+1,h+1,image)){
                       imageArray[h+1][w+1] = WHITE;
                   }
                }
            }
        }


        for (int h =0 ; h < image->height(); h ++){
            for (int w = 0 ; w < image->width() ;w++ ){
                if(imageArray[h][w]==WHITE){
                    image->setPixelColor(w,h,QColor(WHITE,WHITE,WHITE,255));
                }
            }
        }
    }

};
#endif // UTILS_H
