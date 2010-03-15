#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include "task.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

class DragLabel : public QLabel
{
    public:
    //DragLabel(const QString &text, QWidget *parent, int r=0, int g=0, int b=0, int alpha=255);
    //DragLabel(Task trab, const QString &text, QWidget *parent, QColor color = QColor(255,0,0,255), int tamanho = 1);
    DragLabel(const QString &text, QWidget *parent, QString tooltip = "", QColor color = QColor(255,0,0,255), float tamanho = 1.0, bool tempo_setup = false);
    static QString generateString(int num);
    void setTamanho(int t);
    void setCoordenada(QPoint coordenada){this->coordenada=coordenada;}
    void setTtip(QString tooltip){this->tooltip=tooltip;}
    QString getTtip(){return tooltip;}
    QPoint getCoordenada(){return coordenada;}

    protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    private:
    QString labelText;
    QString tooltip;
    bool tempo_setup;
    /*TODO - passar trabalho por mime*/
    //Task trabalho;
    float tamanho;
    int altura;
    QColor cor;
    QPoint coordenada;
    QPoint dragstart;
};
#endif // DRAGLABEL_H
