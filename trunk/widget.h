#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QList>
#include "solucao.h"
#include "ctrabalho.h"

//namespace Ui
//{
//    class WidgetClass;
//}
    QT_BEGIN_NAMESPACE
    class QDragEnterEvent;
    class QDropEvent;
    QT_END_NAMESPACE

class Widget : public QWidget
{


public:
    Widget(Solucao solucao = Solucao::SolucaoVazia(),QWidget *parent = 0);
    //~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QString Widget::generateToolTip(int tam = 1);

    int TIME_UNIT_SIZE;

//private:
    //Ui::WidgetClass *ui;
};

#endif // WIDGET_H
