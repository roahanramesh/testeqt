#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QList>

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
    Widget(QWidget *parent = 0);
    //~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QColor generateColor(int tam = 1);
    QString Widget::generateToolTip(int tam = 1);

//private:
    //Ui::WidgetClass *ui;
};

#endif // WIDGET_H