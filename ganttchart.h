#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QtGui/QWidget>
#include <QList>
#include "ganttscheduling.h"
#include "task.h"
#include "draglabel.h"
#include <QDate>

//namespace Ui
//{
//    class WidgetClass;
//}
    QT_BEGIN_NAMESPACE
    class QDragEnterEvent;
    class QDropEvent;
    QT_END_NAMESPACE

class GanttChart : public QWidget
{

    Q_OBJECT
public:
    GanttChart(GanttScheduling *scheduling,QWidget *parent = 0);
    void desenharTasks(QDate data);
    int getIntervaloInicio(){return intervalo_inicio;}
    void setIntervaloInicio(int num){this->intervalo_inicio=num;}
    int getIntervaloFim(){return intervalo_fim;}
    void setIntervaloFim(int num){this->intervalo_fim=num;}

//    GanttChart get

    QDate getDataAtual(){return data_atual;}
    //~GanttChart();

public slots:
    void redraw(int data_offset);
    void redrawZoom(int newzoom);
    void redrawDate(QDate data);
    void redrawIntervalBegin(int value);
    void redrawIntervalEnd(int value);

//    void resetSize();
//    void desenhaLinhas();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void resetSize();
    QString gerarToolTip(Task trabalho);
    GanttScheduling *scheduling;
    int tamanho_vertical;
    int tamanho_horizontal;
    int y_teto; //define distância entre topo do widget e o desenho do gráfico. é relativo às barras

    int posicao_zero; //define posição zero para o grafico de gantt

    //variáveis utilizadas pra escrever as datas na linha do tempo
    QDate data_atual; //data atual do programa, utilizado como referência pra mostrar para o usuário
    QDate data_inicio;
    QDate data_fim;
    //int dias;
    int intervalo_inicio;
    int intervalo_fim;
    int escala;

//private:
    //Ui::WidgetClass *ui;
};

#endif // GANTTCHART_H
