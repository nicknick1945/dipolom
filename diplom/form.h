#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "platform/defaultwidget.h"
namespace Ui {
class Form;
}

class Form :  public DefaultWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    void onLoad();
    QString* getWidgetName();
    ~Form();

private slots:
    void on_returnButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
