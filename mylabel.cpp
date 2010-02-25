#include "mylabel.h"
#include <QtGui>

void myLabel::setTamanho(int t){
    this->tamanho = t;
}

//myLabel::myLabel(const QString &text, QWidget *parent,int r, int g, int b, int alpha)
//myLabel::myLabel(cTrabalho trab, const QString &text, QWidget *parent, QColor color, int tamanho)
myLabel::myLabel(const QString &text, QWidget *parent, QColor color, float tamanho, bool overhead)
    : QLabel(parent){
    this->coordenada = QPoint(0,0);
    this->overhead = overhead;
    this->tamanho = tamanho;
    //this->trabalho = trab;
    this->cor = color;
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, text);
    //QImage image(size.width() + 12, size.height() + 12,
    //             QImage::Format_ARGB32_Premultiplied);
    int height;
    if(!overhead){
        height = size.height()+12;        //se trabalho for overhead da maquina, desenhar label menor
    }else{
        height = 6;
    }
    //QImage image(tamanho, size.height()+12, QImage::Format_ARGB32_Premultiplied);
    QImage image(tamanho, height, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0,0,0,0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    //Cor do background do label
      //painter.setBrush(Qt::green);
      //painter.setBrush(QColor(r,g,b,127));
    painter.setBrush(cor);
    //Especificação do desenho do label
    //painter.drawRoundedRect(QRectF(0.5, 0.5, image.width()-1, image.height()-1),
                            //25, 25, Qt::RelativeSize);
    painter.drawRect(0,0,image.width()-1,image.height()-1);
    painter.setFont(font);
    //Cor do texto
    painter.setBrush(Qt::green);
    //Define texto do label
    painter.drawText(QRect(QPoint(6,6),size), Qt::AlignCenter,text);
    painter.end();

    setPixmap(QPixmap::fromImage(image));
    labelText = text;
}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
//    if(this->overhead){         //desabilita ação de drag para labels que representarem overhead de maquina
//        //return;
//    }
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    //passar variavel tamanho como float zoa o drop ***FIX***
    dataStream << labelText << QPoint(ev->pos() - rect().topLeft()) << (int)tamanho << cor.red() << cor.green() << cor.blue() << cor.alpha() << overhead << coordenada;

    QMimeData *mimeData = new QMimeData;
    //pra que serve mimeData?
    mimeData->setData("application/x-fridgemagnet", itemData);
    mimeData->setText(labelText);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //o que é o hot spot?
    drag->setHotSpot(ev->pos() - rect().topLeft());
    drag->setPixmap(*pixmap());

    hide();

    //como funciona drag->exec() ?
    if(drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
        close();
    else
        show();
}


QString myLabel::generateString(int num){
    QString str;
     for(int x=0; x<num; x++){
         str.append(" ");
     }
     return str;
}
