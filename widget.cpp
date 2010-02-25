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
#include <QFont>

//coordenada x onde se inicia o desenho do grafico
#define GANTT_START 100
#define LABEL_START 5

#define MAX(a,b) (((a)<(b))?(b):(a))

//#define TIME_UNIT_SIZE 50//multiplicador que modifica a variação de tamanho dos labels. Esta informação deve vir da solução

Widget::Widget(Solucao solucao, QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");

    //Solucao solu = solucao.GerarSolucao();
    //GANTT_START = solucao.getMaiorNomeMaquina();
    TIME_UNIT_SIZE = solucao.get_escala();
    //GANTT_START = 100;//solucao.getMaiorNomeMaquina();


    //float x = GANTT_START;
    //int x = GANTT_START;
    //int x = GANTT_START;
    int x = GANTT_START;
    int y = 20;
    //int count = 0;
    float x_inicio, x_fim;

    QList<int> tamanhos_maquina;
    float posicao_ultimo_trabalho = 0.0;
    float label_pos, label_tamanho;

    QList<QString> nome_maquinas = solucao.getNomeMaquinas();
    //variavel pra iterar a lista com o nome das maquinas
    int indice = 0;
    foreach (QList<cTrabalho> line, solucao.getTrabalhos()){
        QLabel *x_label = new QLabel(nome_maquinas.at(indice),this);
        indice++;
        x_label->move(LABEL_START,y);
        x_label->setMinimumHeight(size.height()+12);
        x_label->show();
        foreach(cTrabalho trab, line){
            x_inicio = trab.getInicio().hour()+(trab.getInicio().minute()/60);
            x_fim = trab.getFim().hour()+(trab.getFim().minute()/60);
            label_pos = x_inicio*TIME_UNIT_SIZE+GANTT_START;
            label_tamanho = trab.getTamanho()*TIME_UNIT_SIZE;
            //myLabel *label = new myLabel(trab,QString::number(label_pos),this,trab.getCor(),label_tamanho);
            myLabel *label = new myLabel(QString::number(label_pos)+" "+QString::number(label_tamanho),this,trab.getCor(),label_tamanho,trab.getOverhead());
            //qDebug(trab.getOverhead()?"hello":"world");
            //myLabel *label = new myLabel(trab.,this,trab.getCor(),label_tamanho);
            posicao_ultimo_trabalho = MAX(label_pos+label_tamanho,posicao_ultimo_trabalho); //utilizado para estabelecer o tamanho horizontal do widget
            label->setToolTip(generateToolTip(10));
            label->move(x_inicio*TIME_UNIT_SIZE+GANTT_START,trab.getOverhead()?y+10:y); //coordenada y = y+10 se label for overhead
            qDebug() << " coord x " << QString::number(x_inicio*TIME_UNIT_SIZE+GANTT_START);
            label->setCoordenada(QPoint(x_inicio*TIME_UNIT_SIZE+GANTT_START,trab.getOverhead()?y+10:y));

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
    tamanho_vertical = MAX(400,solucao.getTrabalhos().size()*70);
    //qDebug()<<QString::number(solu.size());
    setMinimumSize(tamanhos_maquina.last()+100,tamanho_vertical);
    setWindowTitle(tr("Gráfico de Gantt"));
    setAcceptDrops(true);
}


/*
 * Desenha background indicador de tempo
 */
void Widget::paintEvent(QPaintEvent *event){
    QPen label_pen(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen line_pen(Qt::lightGray, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPainter paint(this);
    int TIME_UNIT_SIZE = solucao.get_escala();
    for(int x=0; x<25; x++){
        QString txt = QString::number(x)+":00";
        paint.setPen(label_pen);
        paint.drawText(QPoint(GANTT_START+x*TIME_UNIT_SIZE,10),txt);
        paint.setPen(line_pen);
        paint.drawLine(GANTT_START+x*TIME_UNIT_SIZE,12,GANTT_START+x*TIME_UNIT_SIZE,tamanho_vertical);
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


        //pegar texto do widget original
        QString o_text = mime->text();

        //cTrabalho trabalho = mime->get_

        QString text;
        QPoint offset, coordenada;
        int tamanho, r, g, b, alpha;
        bool overhead;
        //cTrabalho trab;
        dataStream >> text >> offset >> tamanho >> r >> g >> b >> alpha >> overhead >> coordenada;

        myLabel *label = new myLabel(o_text, this, QColor(r,g,b,alpha), tamanho, overhead?true:false);//*TIME_UNIT_SIZE);
        //myLabel *label = new myLabel(o_text, this, QColor(120,200,85,200), event->mimeData()->;
        label->setToolTip(generateToolTip(o_text.toInt()));

        /*restringe drops à coordenada y original, mantendo o label sempre no mesmo nível*/
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
