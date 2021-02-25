#include "platform/mainwindow.h"
#include <QApplication>
#include "platform/defaultwidgetmodel.h"
#include "diplom/startform.h"
#include "diplom/resultfrom.h"
#include <diplom/form.h>
#include <diplom/servicescontext.h>
#include "signal.h"
#include "iostream"
using namespace std;

void fall()
{
      int* p = 0x00000000;
      *p = 13;
}

int memento()
{
    int a=0;
    cout<<"ошибка ну пиздец бежим нахуй отседова"<<endl;
    return 0;
}

void posix_death_signal(int signum)
{
//    fall();
//    memento();
//    signal(signum, SIG_DFL);
    exit(3);

}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, posix_death_signal);
    QApplication a(argc, argv);
    MainWindow w;
    ServicesContext::init();
    w.addWidgets(new DefaultWidgetModel(new StartForm(w.centralWidget())));
    w.addSupProcess(new SubProcessModel(new ResultFrom(w.centralWidget())));
    w.addSupProcess(new SubProcessModel(new Form(w.centralWidget())));
    w.show();

    return a.exec();
}



