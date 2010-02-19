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

#define MAX(a,b) (((a)<(b))?(b):(a))

//#define TIME_UNIT_SIZE 50//multiplicador que modifica a variação de tamanho dos labels. Esta informação deve vir da solução

Widget::Widget(Solucao solucao, QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");

    QList<QList<cTrabalho> > solu = solucao.GerarSolucao();

    TIME_UNIT_SIZE = solucao.get_escala();

    int x = GANTT_START;
    int y = 5;
    int count = 0;
    int x_inicio, x_fim;

    QList<int> tamanhos_maquina;
    int posicao_ultimo_trabalho = 0;
    int label_pos, label_tamanho;

    foreach (QList<cTrabalho> line, solu){
        QLabel *x_label = new QLabel("Máquina "+QString::number(++count),this);
        x_label->move(LABEL_START,y);
        x_label->setMinimumHeight(size.height()+12);
        x_label->show();
        foreach(cTrabalho trab, line){
            x_inicio = trab.getInicio().hour()+(trab.getInicio().minute()/60);
            x_fim = trab.getFim().hour()+(trab.getFim().minute()/60);
            //myLabel *label = new myLabel(QString::number(x_fim-x_inicio),this,trab.getCor(),(x_fim-x_inicio)*TIME_UNIT_SIZE);
            label_pos = x_inicio*TIME_UNIT_SIZE+GANTT_START;
            label_tamanho = trab.getTamanho()*TIME_UNIT_SIZE;
            myLabel *label = new myLabel(QString::number(label_pos),this,trab.getCor(),label_tamanho);
            posicao_ultimo_trabalho = MAX(label_pos+label_tamanho,posicao_ultimo_trabalho);
            //(posicao_ultimo_trabalho < x_inicio*TIME_UNIT_SIZE+GANTT_START+trab.getTamanho())?posicao_ultimo_trabalho=x_inicio*TIME_UNIT_SIZE+GANTT_START+trab.getTamanho():posicao_ultimo_trabalho=posicao_ultimo_trabalho;
            //label->setTamanho(x_fim-x_inicio);
            label->setToolTip(generateToolTip(10));
            //label->move(x_inicio+(x_fim*TIME_UNIT_SIZE-x_inicio*TIME_UNIT_SIZE),y);
            label->move(x_inicio*TIME_UNIT_SIZE+GANTT_START,y);
            label->show();

            //x+=label->width() + 2;
        }
        tamanhos_maquina.append(posicao_ultimo_trabalho);
        posicao_ultimo_trabalho = 0;
        x = GANTT_START;
        y += x_label->height() + 2;
    }
    qSort(tamanhos_maquina);

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //definicao tamanho da tela
    //setMinimumSize(1000, 400);//qMax(200,y));
    //setMinimumSize(Solucao::CalculateX(solucao),400);
    setMinimumSize(tamanhos_maquina.last()+100,400);
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

        myLabel *label = new myLabel(o_text, this, QColor(120,200,85,200), o_text.toInt()*TIME_UNIT_SIZE);
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

QString Widget::generateToolTip(int tam){
    return QString("tamanho : " + QString::number(tam) + "\nmais informações");
}
