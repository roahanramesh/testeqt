#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QtGui/QWidget>
#include <QList>
#include "scheduling.h"
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
    GanttChart(Scheduling *scheduling,QWidget *parent = 0);
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
    QString GanttChart::gerarToolTip(Task trabalho);
    Scheduling *scheduling;
    int tamanho_vertical; //definido pelo construtor, normalmente n�o deve variar durante execu��o
    int tamanho_horizontal;
    int y_teto; //define dist�ncia entre topo do widget e o desenho do gr�fico. � relativo �s barras
    int escala;
    int posicao_zero; //define posi��o zero para o grafico de gantt

    //vari�veis utilizadas pra escrever as datas na linha do tempo
    QDate data_atual; //data atual do programa, utilizado como refer�ncia pra mostrar para o usu�rio
    QDate data_inicio;
    QDate data_fim;
    //int dias;
    int intervalo_inicio;
    int intervalo_fim;

//private:
    //Ui::WidgetClass *ui;
};

#endif // GANTTCHART_H
