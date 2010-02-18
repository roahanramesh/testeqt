#include <QtGui/QApplication>
#include "layoutwidget.h"
#include <QScrollArea>
#include "widget.h"
#include "solucao.h"

//http://doc.trolltech.com/4.6/draganddrop-fridgemagnets.html

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Solucao so;
    //QList<QList<cTrabalho> > solu = so.GerarSolucao();

    layoutWidget w(so);
    //Widget w;
    w.show();
    return a.exec();
}
