#include <QtGui/QApplication>
#include "layoutwidget.h"
#include <QScrollArea>
#include "ganttchart.h"
#include "ganttscheduling.h"

//http://doc.trolltech.com/4.6/draganddrop-fridgemagnets.html

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GanttScheduling so;
    //QList<QList<cTrabalho> > solu = so.GerarSolucao();
    so = GanttScheduling::GerarGanttScheduling();

    layoutWidget w(so);
    //Widget w;
    //w.showMaximized();
    w.show();
    return a.exec();
}
