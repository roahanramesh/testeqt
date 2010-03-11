#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include "ctrabalho.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

class myLabel : public QLabel
{
    public:
    //myLabel(const QString &text, QWidget *parent, int r=0, int g=0, int b=0, int alpha=255);
    //myLabel(cTrabalho trab, const QString &text, QWidget *parent, QColor color = QColor(255,0,0,255), int tamanho = 1);
    myLabel(const QString &text, QWidget *parent, QString tooltip = "", QColor color = QColor(255,0,0,255), float tamanho = 1.0, bool tempo_setup = false);
    static QString generateString(int num);
    void setTamanho(int t);
    void setCoordenada(QPoint coordenada){this->coordenada=coordenada;}
    void setTtip(QString tooltip){this->tooltip=tooltip;}
    QString getTtip(){return tooltip;}
    QPoint getCoordenada(){return coordenada;}

    protected:
    void mousePressEvent(QMouseEvent *ev);
//    void mouseMoveEvent(QMouseEvent *ev);

    private:
    QString labelText;
    QString tooltip;
    bool tempo_setup;
    /*TODO - passar trabalho por mime*/
    //cTrabalho trabalho;
    float tamanho;
    int altura;
    QColor cor;
    QPoint coordenada;
    QPoint dragstart;
};
#endif // MYLABEL_H
