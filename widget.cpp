#include "widget.h"
#include <QtGui>
#include <QString>
#include "mylabel.h"
//#include <QPalette>
//#include "ui_widget.h"
#include "solucao.h"
#include "ctrabalho.h"
#include <iostream>
#include <QDebug>
#include <QPen>

//coordenada x onde se inicia o desenho do grafico
//#define GANTT_START 100
#define LABEL_START 5

#define MAX(a,b) (((a)<(b))?(b):(a))

Widget::Widget(Solucao solucao, QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    solucao.getMaiorNomeMaquina();
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");

    //QList<QList<cTrabalho> > solu = solucao.GerarSolucao();
    //solucao = solucao.GerarSolucao();

    TIME_UNIT_SIZE = solucao.getEscala();

    //varia medida da coluna dos nomes das maquinas
    GANTT_START = MAX(solucao.getMaiorNomeMaquina(),50);//*TIME_UNIT_SIZE;
    //qDebug() << "waddafack " << GANTT_START << TIME_UNIT_SIZE;

    //int x = GANTT_START*LABEL_START+300;
    int y = 20;
    int x_inicio, x_fim;

    QList<int> tamanhos_maquina;
    int posicao_ultimo_trabalho = 0;
    int label_pos, label_tamanho;

    QList<QString> nomes_maquinas = solucao.getNomeMaquinas();
    int iterator_nome_maquinas = 0;
    QString nome_maquina;

    foreach (QList<cTrabalho> line, solucao.getTrabalhos()){
        //QLabel *x_label = new QLabel("Máquina "+QString::number(++count),this);
        QLabel *x_label = new QLabel(nomes_maquinas.at(iterator_nome_maquinas),this);
        iterator_nome_maquinas++;
        x_label->move(LABEL_START,y);
        x_label->setMinimumHeight(size.height()+12);
        x_label->show();
        foreach(cTrabalho trab, line){
            x_inicio = trab.getInicio().hour()+(trab.getInicio().minute()/60);
            x_fim = trab.getFim().hour()+(trab.getFim().minute()/60);
            label_pos = x_inicio*TIME_UNIT_SIZE+GANTT_START;
            label_tamanho = trab.getTamanho()*TIME_UNIT_SIZE;
            //myLabel *label = new myLabel(trab,QString::number(label_pos),this,trab.getCor(),label_tamanho);
            myLabel *label = new myLabel(QString::number(label_pos),this,trab.getCor(),label_tamanho,trab.getOverhead());
            //qDebug(trab.getOverhead()?"hello":"world");
            //myLabel *label = new myLabel(trab.,this,trab.getCor(),label_tamanho);
            posicao_ultimo_trabalho = MAX(label_pos+label_tamanho,posicao_ultimo_trabalho); //utilizado para estabelecer o tamanho horizontal do widget
            label->setToolTip(generateToolTip(10));
            label->move(x_inicio*TIME_UNIT_SIZE+GANTT_START,trab.getOverhead()?y+10:y); //coordenada y = y+10 se label for overhead

            label->setCoordenada(QPoint(x_inicio*TIME_UNIT_SIZE+GANTT_START,trab.getOverhead()?y+10:y));

            label->show();
        }
        tamanhos_maquina.append(posicao_ultimo_trabalho);
        posicao_ultimo_trabalho = 0;
        //x = GANTT_START;
        y += x_label->height() + 2;

        tamanho_vertical = x_label->height() + 2;
    }
    qSort(tamanhos_maquina);

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //definicao tamanho da tela
    //setMinimumSize(1000, 400);//qMax(200,y));
    //setMinimumSize(Solucao::CalculateX(solucao),400);
    tamanho_vertical = MAX(400,solucao.getTrabalhos().size()*70);
    //qDebug()<<QString::number(solucao.getTrabalhos().size());
    setMinimumSize(tamanhos_maquina.last()+100,tamanho_vertical);
    setWindowTitle(tr("Gráfico de Gantt"));
    setAcceptDrops(true);
}


/* TODO - desenhar as retas de forma dinâmica; desenhar labels com o valor das horas; variar de acordo com escala*/
void Widget::paintEvent(QPaintEvent *event){
    QPen pen_linha(Qt::lightGray, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_hora(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPainter paint(this);
    int escala = solucao.getEscala();
    for(int x=0; x<25; x++){
        paint.setPen(pen_hora);
        paint.drawText(QPoint(GANTT_START+x*escala,10),QString::number(x)+":00");
        paint.setPen(pen_linha);
        paint.drawLine(GANTT_START+x*escala,15,GANTT_START+x*escala,tamanho_vertical);

    }
}

void Widget::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Widget::dragMoveEvent(QDragMoveEvent *event){
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Widget::dropEvent(QDropEvent *event){

    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-fridgemagnet");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString o_text = mime->text();

        QString text;
        QPoint offset, coordenada;
        int tamanho, r, g, b, alpha;
        bool overhead;

        dataStream >> text >> offset >> tamanho >> r >> g >> b >> alpha >> overhead >> coordenada;

        myLabel *label = new myLabel(o_text, this, QColor(r,g,b,alpha), tamanho, overhead?true:false);//*TIME_UNIT_SIZE);
        //myLabel *label = new myLabel(o_text, this, QColor(120,200,85,200), event->mimeData()->;
        label->setToolTip(generateToolTip(o_text.toInt()));

        /*restringe drops à coordenada y de origem, mantendo o label sempre no mesmo nível*/
        QPoint pos = event->pos() - offset;
        pos.setY(coordenada.y());
        if(pos.x()<GANTT_START){ pos.setX(GANTT_START); }
        label->move(pos);
        label->setCoordenada(pos);
        //label->move(event->pos() - offset);
        label->show();

        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
                             QString::SkipEmptyParts);
        QPoint position = event->pos();

        foreach (QString piece, pieces) {
            myLabel *label = new myLabel(piece, this);
            label->move(position);
            label->show();

            position += QPoint(label->width(), 0);
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

QString Widget::generateToolTip(int tam){
    return QString("tamanho : " + QString::number(tam) + "\nmais informações");
}
