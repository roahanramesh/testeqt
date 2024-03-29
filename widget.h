#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QList>
#include "solucao.h"
#include "task.h"
#include "mylabel.h"
#include <QDate>

//namespace Ui
//{
//    class WidgetClass;
//}
    QT_BEGIN_NAMESPACE
    class QDragEnterEvent;
    class QDropEvent;
    QT_END_NAMESPACE

class Widget : public QWidget
{

    Q_OBJECT
public:
    Widget(Scheduling scheduling = Scheduling::SchedulingVazia(),QWidget *parent = 0);
    void desenharTrabalhos(QDate data);
    int getIntervaloInicio(){return intervalo_inicio;}
    int getIntervaloFim(){return intervalo_fim;}

    QDate getDataAtual(){return data_atual;}
    //~Widget();

public slots:
    void redraw(int data_offset);
    void redrawZoom(int newzoom);
    void redrawDate(QDate data);
    void redrawIntervalBegin(int value);
    void redrawIntervalEnd(int value);
//    void desenhaLinhas();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QString Widget::gerarToolTip(Task trabalho);
    Scheduling scheduling;
    int tamanho_vertical; //definido pelo construtor
    int tamanho_horizontal;
    int y_teto; //define dist�ncia entre topo do widget e o desenho do gr�fico. � relativo �s barras
    int escala;
    int posicao_zero; //define posi��o zero para o grafico de gantt

    //vari�veis utilizadas pra escrever as datas na linha do tempo
    QDate data_atual; //data atual do programa, utilizado como refer�ncia pra mostrar para o usu�rio
    QDate data_inicio;
    QDate data_fim;
    int dias;
    int intervalo_inicio;
    int intervalo_fim;

//private:
    //Ui::WidgetClass *ui;
};

#endif // WIDGET_H
