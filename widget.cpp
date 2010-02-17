#include "widget.h"
#include <QtGui>
#include <QString>
#include "mylabel.h"
//#include <QPalette>
//#include "ui_widget.h"
#include "solucao.h"
#include "ctrabalho.h"
#include <iostream>

//coordenada x onde se inicia o desenho do grafico
#define GANTT_START 100
#define LABEL_START 5
#define GANTT_LABEL_CEILING 100
#define TIME_UNIT_SIZE 50//multiplicador que modifica a variação de tamanho dos labels

Widget::Widget(QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    //simulação de solução para gerar o grafico
    QList<QList<int> > M_solucao;
    QList<int> L_solucao_1;
    QList<int> L_solucao_2;
    QList<int> L_solucao_3;
    QList<int> L_solucao_4;
    L_solucao_1 << 5 << 2 << 4;
    L_solucao_2 << 2 << 5;
    L_solucao_3 << 7 << 3 << 5 << 6;
    L_solucao_4 << 2 << 6 << 50 << 100;
    M_solucao << L_solucao_1 << L_solucao_2 << L_solucao_3 << L_solucao_4;

    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");

    solucao so;
    QList<QList<cTrabalho> > solu = so.gerarSolucao();

    //labels do topo
//    QLabel *makespan_label = new QLabel("Makespan : n horas", this);
//    makespan_label->move(5,0);
//    makespan_label->setMinimumHeight(size.height()+12);
//    makespan_label->show();
//
//    QLabel *maioratraso_label = new QLabel("Maior atraso : m horas", this);
//    maioratraso_label->move(5,33);
//    maioratraso_label->setMinimumHeight(size.height()+12);
//    maioratraso_label->show();
//
//    QLabel *opatrasadas_label = new QLabel("Numero de Ops atrasadas : k", this);
//    opatrasadas_label->move(5,66);
//    opatrasadas_label->setMinimumHeight(size.height()+12);
//    opatrasadas_label->show();

    int x = GANTT_START;
    int y = GANTT_LABEL_CEILING;
    int count = 0;
    int x_inicio, x_fim;

//    foreach (QList<int> line, M_solucao){
//        QLabel *x_label = new QLabel("Máquina "+QString::number(++count),this);
//        x_label->move(LABEL_START,y);
//        x_label->setMinimumHeight(size.height()+12);
//        x_label->show();
//        foreach(int tamanho, line){
//            //myLabel *label = new myLabel(QString::number(tamanho),this);
//            //myLabel *label = new myLabel(myLabel::generateString(tamanho*5),this,255,0,0);
//            //Gera label com cores diferentes atraves do generateColor()
//                //myLabel *label = new myLabel(myLabel::generateString(tamanho*5),this,generateColor(tamanho));
//            myLabel *label = new myLabel(QString::number(tamanho),this,generateColor(tamanho),tamanho*TIME_UNIT_SIZE);
//
//            label->setTamanho(tamanho);
//            label->setToolTip(generateToolTip(tamanho));
//            label->move(x,y);
//            label->show();
//
//            x+=label->width() + 2;
//        }
//        x = GANTT_START;
//        y += x_label->height() + 2;
//    }

    foreach (QList<cTrabalho> line, solu){
        QLabel *x_label = new QLabel("Máquina "+QString::number(++count),this);
        x_label->move(LABEL_START,y);
        x_label->setMinimumHeight(size.height()+12);
        x_label->show();
        foreach(cTrabalho trab, line){
            x_inicio = trab.getInicio().hour()+(trab.getInicio().minute()/60);
            x_fim = trab.getFim().hour()+(trab.getFim().minute()/60);
            myLabel *label = new myLabel(QString::number(x_fim-x_inicio),this,trab.getCor(),(x_fim-x_inicio)*TIME_UNIT_SIZE);

            //label->setTamanho(x_fim-x_inicio);
            label->setToolTip(generateToolTip(10));
            //label->move(x_inicio+(x_fim*TIME_UNIT_SIZE-x_inicio*TIME_UNIT_SIZE),y);
            label->move(x_inicio*TIME_UNIT_SIZE+GANTT_START,y);
            label->show();

            //x+=label->width() + 2;
        }
        x = GANTT_START;
        y += x_label->height() + 2;
    }

    myLabel *lol = new myLabel("2 horas, inicio 1 hora",this,QColor(175,238,238,255),2*TIME_UNIT_SIZE);
    lol->move(8+1*TIME_UNIT_SIZE,10);
    myLabel *lol1 = new myLabel("2 horas, inicio 3 horas",this,QColor(175,238,238,255),2*TIME_UNIT_SIZE);
    //coordenada x = (num*TIME_UNIT_SIZE) = hora de inicio do trabalho, assumindo ponto inicial = 0 horas
    //             = (8+24*TIME_UNIT_SIZE) = 8 é distancia arbitraria da borda da esquerda, 24 é offset definido pelo trabalho anterior, pode representar um dia.
    //             = +12 = valor arbitrario em mylabel.cpp
    lol1->move(8+3*TIME_UNIT_SIZE,10);
    myLabel *lol2 = new myLabel("3 horas, inicio 5 horas",this,QColor(175,238,238,255),3*TIME_UNIT_SIZE);
    lol2->move(5*TIME_UNIT_SIZE+8,10);
    myLabel *lol3 = new myLabel("2 horas, inicio 8 horas",this,QColor(175,238,238,255),2*TIME_UNIT_SIZE);
    lol3->move(8*TIME_UNIT_SIZE+8,10);
    myLabel *lol4 = new myLabel("5 horas, inicio 15 horas",this,QColor(175,238,238,255),5*TIME_UNIT_SIZE);
    lol4->move(15*TIME_UNIT_SIZE+8,10);
    //lol->setMinimumHeight(size.height()+12);
    //lol->show();

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //definindo layout deste widget
    //QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //definicao tamanho da tela
    setMinimumSize(5000, 400);//qMax(200,y));
    setWindowTitle(tr("Gráfico de Gantt"));
    setAcceptDrops(true);
}

void Widget::dragEnterEvent(QDragEnterEvent *event){
//! [4] //! [5]
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
//! [5] //! [6]
        }
//! [6] //! [7]
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
//! [9] //! [10]
        QByteArray itemData = mime->data("application/x-fridgemagnet");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        //pegar texto do widget original
        QString o_text = mime->text();

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        myLabel *label = new myLabel(o_text, this, generateColor(o_text.toInt()), o_text.toInt()*TIME_UNIT_SIZE);
        label->setToolTip(generateToolTip(o_text.toInt()));
        label->move(event->pos() - offset);
        label->show();

        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
//! [10] //! [11]
        }
//! [11] //! [12]
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

QColor Widget::generateColor(int tam){
    if(tam%2 != 0){
        //deep sky blue
        //return QColor(0,191,255,200);
        //medium sea green
        return QColor(60,197,113,200);
    }else{
        //steel blue
        //return QColor(70,130,180,200);
        //chartreuse
        return QColor(127,255,0,200);
    }
}

QString Widget::generateToolTip(int tam){
    return QString("tamanho : " + QString::number(tam) + "\nmais informações");
}
