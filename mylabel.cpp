#include "mylabel.h"
#include <QtGui>

void myLabel::setTamanho(int t){
    this->tamanho = t;
}

//myLabel::myLabel(const QString &text, QWidget *parent,int r, int g, int b, int alpha)
myLabel::myLabel(const QString &text, QWidget *parent, QColor color, int tamanho)
    : QLabel(parent){
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, text);
    //QImage image(size.width() + 12, size.height() + 12,
    //             QImage::Format_ARGB32_Premultiplied);
    QImage image(tamanho+12, size.height() + 12, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0,0,0,0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    //Cor do background do label
      //painter.setBrush(Qt::green);
      //painter.setBrush(QColor(r,g,b,127));
    painter.setBrush(color);
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
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << labelText << QPoint(ev->pos() - rect().topLeft());

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
