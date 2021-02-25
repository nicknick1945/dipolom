#include "defaultwidget.h"
#include "chache/cachefactory.h"
#include "mainwindow.h"

DefaultWidget::DefaultWidget(QWidget *parent) : QWidget(parent){}

void DefaultWidget::preDestroy()
{

}

void DefaultWidget::onLoad()
{
    logger->info("функция ргодительского класса ");
}

void DefaultWidget::onReturnFromSubProcess()
{

}

void DefaultWidget::returnFromSubProcess()
{
    mainWindow->returnFromSubProcess();
}

void DefaultWidget::setMainWindow(MainWindow *mainWindow_)
{
    mainWindow = mainWindow_;
}

void DefaultWidget::unlockNextButton()
{
    mainWindow->unlockNextButton();
}

void DefaultWidget::lockNextButton()
{
    mainWindow->lockNextNutton();
}

void DefaultWidget::goToSubProcess(QString processName)
{
    mainWindow->goToSubProcess(processName);
}

void DefaultWidget::nextWidget()
{
    mainWindow->next();
}
