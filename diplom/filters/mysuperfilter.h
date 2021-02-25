#ifndef MYSUPERFILTER_H
#define MYSUPERFILTER_H
#include "qhash.h"
#include "qlist.h"
#include "coords.h"
#include <platform/logger/haslogger.h>
#include <QImage>
/**
 * @brief The MySuperFilter class
 * фильтр предназначенный для убирания помех на бинаризованном изображении
 * он убирает с изображения маленькие обькты , размером меньше чем передано в параметрах
 */
using namespace std;

enum PixelType{
    NO_OBJECT,OBJECT
};

class MySuperFilter :public HasLogger {
public:
    MySuperFilter();
    ~MySuperFilter();
    /**
     * @brief doFilte поиск и фильтрация обьектов по размеру, возвращает найденные обекты
     * !!!!(супер пупер важно ) после повторного вызова функции , объекты , которые были до этого созданы
     * будут удалены
     * @param image изображение на котором будем искать объекты
     * @param treshold погор маленькости для обьекта , если найденный обект меньше этого числа , считать его объектом мы не будем
     * @return
     */
    vector<QHash<int,PixelType>*>* doFilter(QImage &image,int treshold) ;

    /**
     * @brief getDescription получить описание того что делает фильтр  (устаревшее , сейчас не надо)
     * @return вернет строку с описанием
     */
    QString* getDescription();

private:
    void clearObjects(vector<QHash<int,PixelType>*>* objects);
    /**
     * @brief map
     * короче прикол в том , что в этом фильтре мы будем проходить по изображению и
     * рекусивно выделять каждый обект который белый ну и соответственно если он меньше заданного
     * пикселей удалять его , но в то же время мы не должны дваджы проходить по одному и тому же месту
     * что очень бы замедлило процесс
     * поэтому создадим карту , в которую будем добавлять пиксели , которые мы уже проходили и считали обектами
     * чтобы все это быстро работало , будем из добавлять в эту карту с пометками
     * NO_RECOGNIZED,NO_OBJECT,OBJECT
     * чтобы пару  х, у мы могли однозначно описать одним числом , будем вписывать туда одно число
     * которое будет ровняться у*10000 + х ; таким образом на изображения накладывается ограниение в размере
     * по координате х до 9999 пикселов
     */
    vector<QHash<int,PixelType>*> *objects = NULL;
    QHash<int,PixelType> *imageMap = NULL;
    int BLACK = 0;
    int WHITE = 255;
    bool contains(Coords &coodrs , int shiftX,int shiftY,const QHash<int,PixelType> *object);
    bool contains(int x, int y,QHash<int,PixelType> *currentMap);
    void putInImageMap(int x, int y,PixelType pixelType);
    void findArea(int stratX, int startY ,QImage &image,int treshold = 50);
    void findAreaRecursive(int stratX, int startY ,QHash<int,PixelType> *currentAreaQHash,QImage &image);
    int culculateKey(int x , int y );
    bool inImageAndNoJustContaintAndWhite(int x, int y ,QHash<int,PixelType> *currentArea ,QImage &image);
    /**
     * @brief inImage функция определяет принадлежит ли точка изображению
     * @param image
     * @param x
     * @param y
     * @return
     */
    bool inImage(int x,int y,QImage &image);
    /**
     * применить все полученные штуки к изображению
     * @brief prepareResultsToImage
     * @param image
     */
    void prepareResultsToImage(QImage &image);
    /** Функция отчистки изображения просто делает картинку черной
     * @brief clearImage
     * @param image
     */
    void clearImage(QImage &image);

    void logImage(QImage image);
};

#endif // MYSUPERFILTER_H
