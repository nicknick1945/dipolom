#include "mysuperfilter.h"
#include "vector"
#include "filterutils.h"
#include "qhash.h"
#include "qlist.h"
using namespace std;

MySuperFilter::MySuperFilter(){}

MySuperFilter::~MySuperFilter()
{
    delete objects;
}

vector<QHash<int,PixelType>*>* MySuperFilter::doFilter(QImage &image, int treshold){
    clearObjects(objects);
    delete imageMap;
    objects  = new vector<QHash<int ,PixelType>*>();
    imageMap = new QHash<int,PixelType>();
    int objectsCount = 0 ;
    logger->info("вход в фильтрцию маленьких обьектов"); 
    for (int h = 0 ; h < image.height() ; h ++ ){
        for (int w = 0 ; w < image.width() ; w++){
            if (FilterUtils::getPixelLight(w,h,image) == WHITE && !contains(w,h,imageMap) ){
                findArea(w,h,image,treshold);
                objectsCount++;
            }
        }
    }
    QString log1 ="найденно обьектиков:";
    log1.append(QString::number(objectsCount));
    logger->debug(log1);
    prepareResultsToImage(image);
    QString log2 = "найдено подходящих объектов";
    log2.append(QString::number(objects->size()));
    logger->debug(log2);
    return objects;
}

void MySuperFilter::findArea(int startX, int startY, QImage &image, int treshold){
    QHash<int,PixelType> *currentAreaMap =new QHash<int,PixelType>();
    findAreaRecursive(startX,startY,currentAreaMap,image);
    QHashIterator<int,PixelType> iter(*currentAreaMap);



    if(currentAreaMap->size()>treshold){
        objects->push_back(currentAreaMap);
        while(iter.hasNext()){
            iter.next();
            imageMap->insert(iter.key(),PixelType::OBJECT) ;
        }
        QString msg = "размер обьектика : ";
        msg.append(QString::number(currentAreaMap->size()));
        logger->debug(msg);
    }else{
        while(iter.hasNext()){
            iter.next();
            imageMap->insert(iter.key(),PixelType::NO_OBJECT) ;
        }
    }
}

void MySuperFilter::findAreaRecursive(int startX, int startY, QHash<int,PixelType> *currentAreaMap,QImage &image){
    currentAreaMap->insert(culculateKey(startX,startY),PixelType::NO_OBJECT);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY,currentAreaMap,image)) findAreaRecursive(startX+1,startY,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY,currentAreaMap,image)) findAreaRecursive(startX-1,startY,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX,startY-1,currentAreaMap,image)) findAreaRecursive(startX,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX,startY+1,currentAreaMap,image)) findAreaRecursive(startX,startY+1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY-1,currentAreaMap,image)) findAreaRecursive(startX-1,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY+1,currentAreaMap,image)) findAreaRecursive(startX-1,startY+1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY-1,currentAreaMap,image)) findAreaRecursive(startX+1,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY+1,currentAreaMap,image)) findAreaRecursive(startX+1,startY+1,currentAreaMap,image);
}



void MySuperFilter::prepareResultsToImage(QImage &image){
    clearImage(image);
    //skiletization();
    for (int count = 0 ; count < objects->size() ; count++){
        QHashIterator<int,PixelType> iter(*objects->at(count));
        while(iter.hasNext()){
            iter.next();
            int coordX = iter.key()%10000;
            int coordY = iter.key()/10000;
            image.setPixelColor(coordX,coordY,QColor(WHITE,WHITE,WHITE,255));
        }
    }

}

void MySuperFilter::putInImageMap(int x, int y , PixelType pixelType){
    imageMap->insert(culculateKey(x,y),pixelType);
}

bool MySuperFilter::contains(int x, int y,QHash<int,PixelType> *currentMap){
    return currentMap->contains(culculateKey(x,y));
}

QString *MySuperFilter::getDescription(){
    QString *description = new QString("мой фильтр для убирания помех");
    return description;
}

void MySuperFilter::clearObjects(vector<QHash<int, PixelType> *> * objects)
{
    if(objects!=NULL){
        for (int i = 0 ; i < objects->size() ;i++){
            delete objects->at(i);
        }
        objects->clear();
    }
}


bool MySuperFilter::contains(Coords &coords, int shiftX, int shiftY,const QHash<int,PixelType> *object)
{
    if (coords.getY() + shiftY < 0 ) return false;
    if (coords.getX() + shiftX < 0 ) return false;
    return object->contains(culculateKey(coords.getX()+shiftX,coords.getY()+shiftY));
}

bool MySuperFilter::inImage( int x, int y,QImage &image){
    return x >= 0 && x <= (image.width() - 1 ) && y >=0 && y <= (image.height() -1 );
}

int MySuperFilter::culculateKey(int x, int y){
    return x+y*10000 ;
}

bool MySuperFilter::inImageAndNoJustContaintAndWhite(int x, int y, QHash<int,PixelType> *currentArea, QImage &image){
    return  inImage(x,y,image)&&(!contains(x,y,currentArea))&&(FilterUtils::getPixelLight(x,y,image) == WHITE);
}

void MySuperFilter::clearImage(QImage &image){
    for (int h = 0 ; h < image.height() ; h ++){
         for (int w = 0 ; w  <image.width() ; w++){
             image.setPixelColor(w,h,QColor(BLACK,BLACK,BLACK,255));
         }
    }
}

void MySuperFilter::logImage(QImage image)
{
    QString srt;
    for (int h = 0 ; h < image.height(); h ++){
        QString line;
        for (int w = 0 ; w < image.width() ; w++){
            line.append(QString::number(image.pixelColor(w,h).blue()));
        }
        srt.append(line);
        srt.append("/n");
    }

    logger->debug(srt);
}
