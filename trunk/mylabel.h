#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

class myLabel : public QLabel
{
    public:
    //myLabel(const QString &text, QWidget *parent, int r=0, int g=0, int b=0, int alpha=255);
    myLabel(const QString &text, QWidget *parent, QColor color = QColor(255,0,0,255), int tamanho = 1);
    static QString generateString(int num);
    void setTamanho(int t);

    protected:
    void mousePressEvent(QMouseEvent *ev);

    private:
    QString labelText;
    int tamanho;
};
#endif // MYLABEL_H
