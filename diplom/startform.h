#ifndef STARTFORM_H
#define STARTFORM_H

#include "platform/defaultwidget.h"

namespace Ui {
class StartForm;
}

class StartForm : public DefaultWidget
{
    Q_OBJECT
public:
    explicit StartForm(QWidget *parent = 0);
    QString* getWidgetName();
    ~StartForm();
private slots:
    void on_downloadImageButton_clicked();
    void on_fileterButton_clicked();

    void on_binarizationButton_clicked();

    void on_allAcinusButton_clicked();

    void on_healthAcinusButton_clicked();

    void on_threadGlissonButton_clicked();

    void on_forthGlissonButton_clicked();

    void on_findAnalogInDb_clicked();

    virtual void onReturnFromSubProcess();

    void on_pushButton_clicked();

    void on_gistButton_clicked();

private:

    void prepareAcinusToImage(QString *type,bool all= false);

    Ui::StartForm *ui;
};

#endif // STARTFORM_H
