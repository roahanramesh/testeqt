#include <QtGui/QApplication>
#include "layoutwidget.h"
#include <QScrollArea>
#include "widget.h"

//http://doc.trolltech.com/4.6/draganddrop-fridgemagnets.html

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    layoutWidget w;
    //Widget w;
    w.show();
    return a.exec();
}
