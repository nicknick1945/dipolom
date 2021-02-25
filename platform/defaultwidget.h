#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H
#include "qwidget.h"
#include "chache/cache.h"
#include "chache/cachefactory.h"

#include <platform/logger/haslogger.h>


class MainWindow;

class DefaultWidget : public QWidget, public HasLogger
{
    Q_OBJECT
public:
    explicit DefaultWidget(QWidget *parent = 0);
    virtual QString* getWidgetName()=0;
    virtual void preDestroy();
    virtual void onLoad();
    virtual void onReturnFromSubProcess();
    virtual void returnFromSubProcess();
    void setMainWindow(MainWindow *mainWindow_);
    void unlockNextButton();
    void lockNextButton();
    virtual void goToSubProcess(QString processName);

signals:

protected:
    void nextWidget();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();
private:
    MainWindow *mainWindow;
};


#endif // DEFAULTWIDGET_H
