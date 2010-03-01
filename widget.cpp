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

    escala = solucao.getEscala();
    //y_teto = 20;
    //espaço para numero da data
    y_teto = 60;

    //varia medida da coluna dos nomes das maquinas
    posicao_zero = MAX(solucao.getMaiorNomeMaquina(),50);//*escala;
    //qDebug() << "waddafack " << GANTT_START << escala;

    //int x = GANTT_START*LABEL_START+300;
    int y = y_teto;
    float x_inicio, x_fim;

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
            x_inicio = trab.getInicioFloat();
            x_fim = trab.getFimFloat();

            label_pos = x_inicio*escala+posicao_zero;
            label_tamanho = trab.getTamanho()*escala;

            myLabel *label = new myLabel(trab.getTexto(),this,gerarToolTip(trab),trab.getCor(),label_tamanho,trab.getOverhead());

            posicao_ultimo_trabalho = MAX(label_pos+label_tamanho,posicao_ultimo_trabalho); //utilizado para estabelecer o tamanho horizontal do widget
            label->setTtip(gerarToolTip(trab));
            label->setToolTip(label->getTtip());
            label->move(x_inicio*escala+posicao_zero,trab.getOverhead()?y+10:y); //coordenada y = y+10 se label for overhead

            label->setCoordenada(QPoint(x_inicio*escala+posicao_zero , trab.getOverhead()?y+10:y));

            //qDebug() << "data inicio: " << trab.getDataInicio().toString() << "data fim: " << trab.getDataFim().toString();
            //int wat = trab.getDataInicio().daysTo(trab.getDataFim());
            qDebug() << QString::number(solucao.getDiasDuracao());


            label->show();
        }
        tamanhos_maquina.append(posicao_ultimo_trabalho);
        posicao_ultimo_trabalho = 0;

        y += x_label->height() + 2;

        tamanho_vertical = x_label->height() + 2;
    }
    qSort(tamanhos_maquina);

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //definicao tamanho da tela

    tamanho_vertical = MAX(400,solucao.getTrabalhos().size()*70);
    setMinimumSize(tamanhos_maquina.last()+100,tamanho_vertical);
    setWindowTitle(tr("Gráfico de Gantt"));
    setAcceptDrops(true);
}


/* TODO - desenhar as retas de forma dinâmica; desenhar labels com o valor das horas; variar de acordo com escala*/
void Widget::paintEvent(QPaintEvent *event){
    QPen pen_linha(Qt::lightGray, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_meiahora(Qt::lightGray, 0, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_hora(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_bkp;
    QFont font_data = QFont();
    font_data.setPointSize(16);
    QPainter paint(this);
    int escala = solucao.getEscala();
    float linha_meiahora = 0;
    float linha_45min = 0;
    float linha_15min = 0;
    for(int x=0; x<24; x++){
        if(x==0 || x==12){ //escreve data no topo da linha do tempo
            paint.setFont(font_data);
            pen_bkp = paint.pen();
            paint.setPen(QPen());
            paint.drawText(QPoint(posicao_zero+x*escala,y_teto-30),"01/03");
            paint.setFont(QFont());
            paint.setPen(pen_bkp);
        }
        paint.setPen(pen_hora);
        paint.drawText(QPoint(posicao_zero+x*escala,y_teto-10),QString::number(x)+((escala>=25)?":00":""));
        paint.setPen(pen_linha);
        paint.drawLine(posicao_zero+x*escala , y_teto-5 , posicao_zero+x*escala , tamanho_vertical);
        paint.setPen(pen_meiahora);

        linha_meiahora = ((posicao_zero+x*escala)+(posicao_zero+(x+1)*escala))/2;
        if(escala>=100)
        paint.drawText(QPoint(linha_meiahora,y_teto-10),":30");
        paint.drawLine(linha_meiahora,y_teto-5,linha_meiahora,tamanho_vertical);

        linha_45min = (linha_meiahora+(posicao_zero+(x+1)*escala))/2;
        if(escala>=100)
        paint.drawText(QPoint(linha_45min,y_teto-10),":45");
        paint.drawLine(linha_45min,y_teto-5,linha_45min,tamanho_vertical);

        linha_15min = ((posicao_zero+x*escala)+linha_meiahora)/2;
        if(escala>=100)
        paint.drawText(QPoint(linha_15min,y_teto-10),":15");
        paint.drawLine(linha_15min,y_teto-5,linha_15min,tamanho_vertical);
        //paint.drawLine(GANTT_START+(x+1/2)*escala,15,GANTT_START+(x+1/2)*escala,tamanho_vertical);
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

        QString text, tooltip;
        QPoint offset, coordenada;
        int tamanho, r, g, b, alpha;
        bool overhead;

        dataStream >> text >> tooltip >> offset >> tamanho >> r >> g >> b >> alpha >> overhead >> coordenada;

        myLabel *label = new myLabel(o_text,this,tooltip, QColor(r,g,b,alpha), tamanho, overhead?true:false);//*escala);
        //myLabel *label = new myLabel(o_text, this, QColor(120,200,85,200), event->mimeData()->;
        label->setToolTip(tooltip);

        /*restringe drops à coordenada y de origem, mantendo o label sempre no mesmo nível*/
        QPoint pos = event->pos() - offset;
        pos.setY(coordenada.y());
        if(pos.x()<posicao_zero){ pos.setX(posicao_zero); }
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

QString Widget::gerarToolTip(cTrabalho trabalho){
    //return QString("tamanho : " + QString::number(tam) + "\nmais informações");
    QString tooltip;
    tooltip = trabalho.getTexto() + "\nOrdem de produção: " + trabalho.getOrdemProducao();
    tooltip += "\nPilha: " + trabalho.getPilha();
    tooltip += "\nProduto: " + trabalho.getProduto();
    tooltip += "\nAcabamento: " + trabalho.getAcabamento();
    tooltip += "\nMaterial Base: " + trabalho.getMaterialBase();
    tooltip += "\nQtd Peças: " + trabalho.getQtdPecas();
    tooltip += "\nData inicio: ";
    tooltip += "xx/xx/xx "+QString::number(trabalho.getInicio().hour());
    tooltip += ":"+QString::number(trabalho.getInicio().minute());
    tooltip += "\nData fim: ";
    tooltip += "yy/yy/yy " + QString::number(trabalho.getFim().hour());
    tooltip += ":"+QString::number(trabalho.getFim().minute());
    //tooltip.append(trabalho.getInicio().toString("hh:mm"));
    return tooltip;
}
