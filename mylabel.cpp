#include "mylabel.h"
#include <QtGui>

void myLabel::setTamanho(int t){
    this->tamanho = t;
}

//myLabel::myLabel(const QString &text, QWidget *parent,int r, int g, int b, int alpha)
//myLabel::myLabel(cTrabalho trab, const QString &text, QWidget *parent, QColor color, int tamanho)
myLabel::myLabel(const QString &text,QWidget *parent,QString tooltip, QColor color, float tamanho, bool tempo_setup)
    : QLabel(parent){
    this->coordenada = QPoint(0,0);
    this->tempo_setup = tempo_setup;
    this->tamanho = tamanho;
    this->tooltip = tooltip;
    //this->trabalho = trab;
    this->cor = color;
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, text);
    //QImage image(size.width() + 12, size.height() + 12,
    //             QImage::Format_ARGB32_Premultiplied);
    int height;
    if(!tempo_setup){
        height = size.height()+12;        //se trabalho for tempo_setup da maquina, desenhar label menor
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
    painter.setBrush(cor);
    //Especificação do desenho do label
    painter.drawRect(0,0,image.width(),image.height());
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
//    if(this->tempo_setup){         //desabilita ação de drag para labels que representarem tempo_setup de maquina
//        //return;
//    }
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    //passar variavel tamanho como float zoa o drop
    dataStream << labelText << tooltip << QPoint(ev->pos() - rect().topLeft()) << (int)tamanho << cor.red() << cor.green() << cor.blue() << cor.alpha() << tempo_setup << coordenada;

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
