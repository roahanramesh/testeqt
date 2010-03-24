#include "ganttchart.h"
#include <QtGui>
#include <QString>
#include "draglabel.h"
//#include <QPalette>
//#include "ui_ganttchart.h"
#include "ganttscheduling.h"
#include "task.h"
#include <iostream>
#include <QDebug>
#include <QPen>
#include <QFont>
#include <QTime>

//coordenada x onde se inicia o desenho do grafico
//#define GANTT_START 100
#define LABEL_START 5

#define MAX(a,b) (((a)<(b))?(b):(a))

GanttChart::GanttChart(GanttScheduling *scheduling, QWidget *parent)
    : QWidget(parent)//, ui(new Ui::WidgetClass)
{
    this->scheduling = scheduling;
    escala = scheduling->getEscala();

    data_inicio = scheduling->getDataInicio();
    data_atual = data_inicio;
    data_fim = scheduling->getDataFinal();
//    this->dias = 1;

    this->intervalo_inicio = scheduling->getHoraInicio(QDate::currentDate()).hour();
    this->intervalo_fim = scheduling->getHoraFinal(QDate::currentDate()).hour();

//    for(int x=0 ; x<data_inicio.daysTo(data_fim) ; x++){
//        dias++;
//    }

    //espaço vertical para escrever data
    y_teto = 60;

    desenharTasks(QDate::currentDate());

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);
    //resetSize();
    //definicao tamanho da tela
    tamanho_vertical = MAX(800,scheduling->getTasks().size()*70);
    //setMinimumSize(lista_tamanhos_cel_trabalho.last()+100,tamanho_vertical);
    //setMinimumSize(tamanho_horizontal,tamanho_vertical);
    //SetMinimumSize(50000,400);
    //setMinimumSize(scheduling->getMaiorNomeCelulaTrabalho()+(24*scheduling->getEscala())+100,tamanho_vertical);
    //setMinimumSize(scheduling->getHoraFinal(
    //setFixedSize(scheduling->getMaiorNomeCelulaTrabalho()+(24*scheduling->getEscala())+100,tamanho_vertical);
    setFixedSize(tamanho_horizontal+50,tamanho_vertical);
    setWindowTitle(tr("Gráfico de Gantt"));
    setAcceptDrops(true);
}

void GanttChart::redraw(int data_offset){
    QList<DragLabel *> mylist = this->findChildren<DragLabel*>();
    foreach(DragLabel* wut, mylist) wut->deleteLater();
//    QList<QObject*> mylist = this->children();
//    foreach(QObject* wut, mylist) wut->deleteLater();
    if(data_offset == 0){
        data_atual = QDate::currentDate();
    } else {
    //qDebug() << data_atual.toString();
        data_atual = data_atual.addDays(data_offset);
    }
    desenharTasks(data_atual);
    //resetSize();
    update();
}

void GanttChart::resetSize(){
    //int valor = ((intervalo_fim-intervalo_inicio)*scheduling->getEscala()+posicao_zero);
    //this->setFixedSize(valor,800);
    //this->setFixedSize(tamanho_horizontal,tamanho_vertical);
//    this->adjustSize();
//    qsrand(QTime::currentTime().msec());
//    if(qrand()%2 == 0)
//        this->setVisible(false);
//    else
//        this->setVisible(true);
//    this->setFixedSize(qrand()%1000,qrand()%1000);
    this->setFixedSize(tamanho_horizontal+50,tamanho_vertical);
    //qDebug() << "resetSize called" << tamanho_horizontal << tamanho_vertical;
}

void GanttChart::redrawDate(QDate data){
    QList<DragLabel *> mylist = this->findChildren<DragLabel*>();
    foreach(DragLabel* wut, mylist) wut->deleteLater();
    data_atual = data;
    //setMinimumSize(400,400);
    desenharTasks(data_atual);
    update();
}

void GanttChart::redrawZoom(int newzoom){
//    QList<DragLabel *> mylist = this->findChildren<DragLabel*>();
//    foreach(DragLabel* wut, mylist) wut->deleteLater();
    QList<QObject*> mylist = this->children();
    foreach(QObject* wut, mylist) wut->deleteLater();
    int nova_escala = this->scheduling->getEscala()+(newzoom*5);
    if(nova_escala >=15)
        this->scheduling->setEscala(nova_escala);
    desenharTasks(data_atual);
    update();
}

void GanttChart::redrawIntervalBegin(int value){
    //qDebug() << "redrawIntervalBegin " << QString::number(value);
    QList<QObject*> mylist = this->children();
    foreach(QObject* wut, mylist) wut->deleteLater();
    intervalo_inicio = value;
    desenharTasks(data_atual);
    update();
}

void GanttChart::redrawIntervalEnd(int value){
    //qDebug() << "redrawIntervalEnd " << QString::number(value);
    QList<QObject*> mylist = this->children();
    foreach(QObject* wut, mylist) wut->deleteLater();
    intervalo_fim = value;
    desenharTasks(data_atual);
    update();
}

void GanttChart::desenharTasks(QDate data){
    //desenharTasks(QDate::currentDate().addDays(0));
    //qDebug() << scheduling->isDiaVazio(data);
    this->escala = scheduling->getEscala();
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, " ");
    int y = y_teto;
    posicao_zero = MAX(this->scheduling->getMaiorNomeCelulaTrabalho(),50);
    float x_inicio;

    QList<int> lista_tamanhos_cel_trabalho;
    int posicao_ultimo_task = 0;
    int label_pos, label_tamanho;

    QList<QString> nomes_celulas_trabalho = this->scheduling->getNomeCelulasTrabalho();
    int iterator_nome_celulas_trabalho = 0;
    QString nome_celula_trabalho;

    //define data a ser desenhada
    //data_atual = data;//QDate::currentDate().addDays(1);
    foreach (QList<Task> celula_trabalho, this->scheduling->getTasks()){
        QLabel *x_label = new QLabel(nomes_celulas_trabalho.at(iterator_nome_celulas_trabalho),this);
        iterator_nome_celulas_trabalho++;
        x_label->move(LABEL_START,y);
        x_label->setMinimumHeight(size.height()+12);
        x_label->show();
        foreach(Task task, celula_trabalho){
            if(task.getDataInicio() == data_atual){
                x_inicio = this->scheduling->getCoordTask(task);
                x_inicio -= intervalo_inicio;//x_inicio-(intervalo_fim-intervalo_inicio);
                //qDebug() << QString::number(x_inicio*escala);

                label_pos = (int)(x_inicio*escala+posicao_zero);

                label_tamanho = (int)(task.getTamanho()*escala);
//                int testeint = (int)(task.getInicio().secsTo(task.getFim())/(3600))*escala;
                posicao_ultimo_task = MAX(label_pos+label_tamanho,posicao_ultimo_task); //utilizado para estabelecer o tamanho horizontal do widget

                //exibe label se ele não começar antes da posição_zero
                if(x_inicio*escala+posicao_zero>=posicao_zero){
                    DragLabel *label = new DragLabel(task.getTexto(),this,gerarToolTip(task),task.getCor(),label_tamanho,task.getTempoSetup());

                    label->setTtip(gerarToolTip(task));
                    label->setToolTip(label->getTtip());
                    label->move(x_inicio*escala+posicao_zero,task.getTempoSetup()?y+10:y); //coordenada y = y+10 se label for overhead

                    label->setCoordenada(QPoint(x_inicio*escala+posicao_zero , task.getTempoSetup()?y+10:y));
//                    if(task.getDataInicio().daysTo(datahoje)){
                    label->show();
                }
            }

        }
        lista_tamanhos_cel_trabalho.append(posicao_ultimo_task);
        posicao_ultimo_task = 0;

        y += x_label->height() + 2;

        //tamanho_vertical = x_label->height() + 2;
    }
    qSort(lista_tamanhos_cel_trabalho);
    this->tamanho_horizontal = lista_tamanhos_cel_trabalho.last();//+100;
    resetSize();
}

void GanttChart::paintEvent(QPaintEvent *event){
    //qDebug() << "paint event =D " << QString::number(scheduling->getEscala());

    //alguma coisa muda valor de tamanho_vertical, necessario resetar seu valor
    tamanho_vertical = MAX(400,scheduling->getTasks().size()*70);

    QPen pen_linha(Qt::lightGray, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_meiahora(Qt::lightGray, 0, Qt::DotLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_hora(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    QPen pen_bkp;
    QFont font_data = QFont();
    font_data.setPointSize(16);
    QPainter *paint = new QPainter(this);

    QDate dia = this->data_atual;
    QString texto_dia;
    int escala = scheduling->getEscala();
    float linha_meiahora = 0;
    float linha_45min = 0;
    float linha_15min = 0;


//    dias = 2;
    //for(int y=0 ; y<dias ; y++){

        //for(int x=24*y; x<24+(y*24); x++){
        //for(int x=0; x<24; x++){
    int x_hora = intervalo_inicio;
    //int fim_laco = ;
//    if(intervalo_fim-intervalo_inicio < 0)
//        x_hora = 0;
    //qDebug() << intervalo_inicio << intervalo_fim;
    if(scheduling->isDiaVazio(data_atual)){
        //qDebug() << scheduling->isDiaVazio(data_atual);
        intervalo_inicio = 0;
        intervalo_fim = 24;
        this->setFixedSize(posicao_zero+(24*escala),400);
    }
    for(int x = 0; x<=(intervalo_fim==23?(intervalo_fim-intervalo_inicio)+1:(intervalo_fim-intervalo_inicio)) ; x++){
        //int x_hora = x;
        //int x_hora = intervalo_inicio;

        //escreve data no topo da linha do tempo
//        if(x_hora == 0 || x_hora == 12){
//            paint->setFont(font_data);
//            pen_bkp = paint->pen();
//            paint->setPen(QPen());
//            paint->drawText(QPoint(posicao_zero+x*escala,y_teto-30),dia.toString("dd/MM"));
//            //paint->drawText(QPoint(posicao_zero+x*escala,y_teto-30),data_atual.toString("dd/MM"));
//            if(x_hora == 12)
//                dia = dia.addDays(1);
//            paint->setFont(QFont());
//            paint->setPen(pen_bkp);
//        }

//            if(x_hora == 12)
//                    dia = dia.addDays(1);
        paint->setPen(pen_hora);
        paint->drawText(QPoint(posicao_zero+x*escala,y_teto-10),QString::number(x_hora==24?0:x_hora)+((escala>=25)?":00":""));
        paint->setPen(pen_linha);
        paint->drawLine(posicao_zero+x*escala , y_teto-5 , posicao_zero+x*escala , tamanho_vertical);
        paint->setPen(pen_meiahora);

        linha_meiahora = ((posicao_zero+x*escala)+(posicao_zero+(x+1)*escala))/2;
        if(escala>=100)
        paint->drawText(QPoint(linha_meiahora,y_teto-10),":30");
        paint->drawLine(linha_meiahora,y_teto-5,linha_meiahora,tamanho_vertical);

        linha_45min = (linha_meiahora+(posicao_zero+(x+1)*escala))/2;
        if(escala>=100)
        paint->drawText(QPoint(linha_45min,y_teto-10),":45");
        paint->drawLine(linha_45min,y_teto-5,linha_45min,tamanho_vertical);

        linha_15min = ((posicao_zero+x*escala)+linha_meiahora)/2;
        if(escala>=100)
        paint->drawText(QPoint(linha_15min,y_teto-10),":15");
        paint->drawLine(linha_15min,y_teto-5,linha_15min,tamanho_vertical);
        //paint.drawLine(GANTT_START+(x+1/2)*escala,15,GANTT_START+(x+1/2)*escala,tamanho_vertical);
        x_hora++;
    }
    //}
    delete paint;
//    qsrand(QTime::currentTime().msec());
//    this->setFixedSize(qrand()%500,qrand()%500);
    //desenharTasks(QDate::currentDate());
    //qDebug() << "paintEvent called, y_teto, tamanho vertical: " << qrand() << y_teto << tamanho_vertical;
}

void GanttChart::dragEnterEvent(QDragEnterEvent *event){
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

void GanttChart::dragMoveEvent(QDragMoveEvent *event){
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

void GanttChart::dropEvent(QDropEvent *event){
//    update();
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-fridgemagnet");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString o_text = mime->text();

        QString text, tooltip;
        QPoint offset, coordenada;
        int tamanho, r, g, b, alpha;
        bool tempo_setup;

        dataStream >> text >> tooltip >> offset >> tamanho >> r >> g >> b >> alpha >> tempo_setup >> coordenada;

        DragLabel *label = new DragLabel(o_text,this,tooltip, QColor(r,g,b,alpha), tamanho, tempo_setup?true:false);//*escala);
        //DragLabel *label = new DragLabel(o_text, this, QColor(120,200,85,200), event->mimeData()->;
        label->setToolTip(tooltip);

        /*restringe drops à coordenada y de origem, mantendo o label sempre no mesmo nível*/
        QPoint pos = event->pos() - offset;
        pos.setY(coordenada.y());
        if(pos.x()<posicao_zero){ pos.setX(posicao_zero); }

        /*
          * SNIPPET PRA ACHAR A HORA DO DROP
          */
        //qDebug() << "hora: " << ((float)(pos.x()-posicao_zero)/escala)+intervalo_inicio;  // <==== formula pra achar a hora da posição do drop
        float hora_float = ((float)(pos.x()-posicao_zero)/escala)+intervalo_inicio;
        int hora_int = (int)hora_float;
        float minutos = hora_float - hora_int;
        QTime novotempo = QTime(hora_int,minutos*60);
        //qDebug() << hora_float << hora_int << minutos*60;
        qDebug() << novotempo;

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
            DragLabel *label = new DragLabel(piece, this);
            label->move(position);
            label->show();

            position += QPoint(label->width(), 0);
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

QString GanttChart::gerarToolTip(Task task){
    //return QString("tamanho : " + QString::number(tam) + "\nmais informações");
    QString tooltip;
    tooltip = task.getTexto() + "\nOrdem de produção: " + task.getOrdemProducao();
    tooltip += "\nPilha: " + task.getPilha();
    tooltip += "\nProduto: " + task.getProduto();
    tooltip += "\nAcabamento: " + task.getAcabamento();
    tooltip += "\nMaterial Base: " + task.getMaterialBase();
    tooltip += "\nQtd Peças: " + task.getQtdPecas();
    tooltip += "\nData inicio: ";
    tooltip += task.getDataInicio().toString("dd/MM/yy ")+QString::number(task.getInicio().time().hour());
    tooltip += ":"+QString::number(task.getInicio().time().minute());
    tooltip += "\nData fim: ";
    tooltip += task.getDataFim().toString("dd/MM/yy ") + QString::number(task.getFim().time().hour());
    tooltip += ":"+QString::number(task.getFim().time().minute());
    //tooltip.append(task.getInicio().toString("hh:mm"));
    return tooltip;
}
