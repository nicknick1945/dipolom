#ifndef RESULTFROM_H
#define RESULTFROM_H

#include <QWidget>
#include <diplom/database/vo/imagedbmodel.h>
#include "platform/defaultwidget.h"

namespace Ui {
class ResultFrom;
}

class ResultFrom : public DefaultWidget
{
    Q_OBJECT

public:
    explicit ResultFrom(QWidget *parent = 0);
    void onLoad();

    QString* getWidgetName();
    ~ResultFrom();


private slots:
    void on_previousImageButton_clicked();
    void on_pushButton_clicked();
    void on_nextImageButton_clicked();

private:
    QList<ImageDbModel*> *fromDbList;
    Ui::ResultFrom *ui;
    int iter;
    void setImageToSceneFromBd(QImage* image);
    void setImageToScene();
};

#endif // RESULTFROM_H
