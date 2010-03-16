#include <QtGui/QApplication>
#include "layoutwidget.h"
#include <QScrollArea>
#include "ganttchart.h"
#include "scheduling.h"

//http://doc.trolltech.com/4.6/draganddrop-fridgemagnets.html

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scheduling so;
    //QList<QList<cTrabalho> > solu = so.GerarSolucao();
    so = Scheduling::GerarScheduling();

    layoutWidget w(so);
    //Widget w;
    w.show();
    return a.exec();
}
