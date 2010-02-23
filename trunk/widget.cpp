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

//coordenada x onde se inicia o desenho do grafico
#define GANTT_START 100
#define LABEL_START 5

#define MAX(a,b) (((a)<(b))?(b):(a))

//#define TIME_UNIT_SIZE 50//multiplicador que modifica a varia��o de tamanho dos labels. Esta informa��o deve vir da solu��o

Widget::Widget(Solucao solucao, QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");

    QList<QList<cTrabalho> > solu = solucao.GerarSolucao();

    TIME_UNIT_SIZE = solucao.get_escala();

    int x = GANTT_START;
    int y = 20;
    int count = 0;
    int x_inicio, x_fim;

    QList<int> tamanhos_maquina;
    int posicao_ultimo_trabalho = 0;
    int label_pos, label_tamanho;
    int tamanho_vertical;

    foreach (QList<cTrabalho> line, solu){
        QLabel *x_label = new QLabel("M�quina "+QString::number(++count),this);
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
            qDebug(trab.getOverhead()?"hello":"world");
            //myLabel *label = new myLabel(trab.,this,trab.getCor(),label_tamanho);
            posicao_ultimo_trabalho = MAX(label_pos+label_tamanho,posicao_ultimo_trabalho); //utilizado para estabelecer o tamanho horizontal do widget
            label->setToolTip(generateToolTip(10));
            label->move(x_inicio*TIME_UNIT_SIZE+GANTT_START,trab.getOverhead()?y+10:y);     //coordenada y = y+10 se label for overhead
            label->show();
        }
        tamanhos_maquina.append(posicao_ultimo_trabalho);
        posicao_ultimo_trabalho = 0;
        x = GANTT_START;
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
    tamanho_vertical = MAX(400,solu.size()*70);
    qDebug()<<QString::number(solu.size());
    setMinimumSize(tamanhos_maquina.last()+100,tamanho_vertical);
    setWindowTitle(tr("Gr�fico de Gantt"));
    setAcceptDrops(true);
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


        //pegar texto do widget original
        QString o_text = mime->text();

        //cTrabalho trabalho = mime->get_

        QString text;
        QPoint offset;
        int tamanho, r, g, b, alpha;
        //cTrabalho trab;
        dataStream >> text >> offset >> tamanho >> r >> g >> b >> alpha;

        myLabel *label = new myLabel(o_text, this, QColor(r,g,b,alpha), tamanho);//*TIME_UNIT_SIZE);
        //myLabel *label = new myLabel(o_text, this, QColor(120,200,85,200), event->mimeData()->;
        label->setToolTip(generateToolTip(o_text.toInt()));
        label->move(event->pos() - offset);
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
    return QString("tamanho : " + QString::number(tam) + "\nmais informa��es");
}