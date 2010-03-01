#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QList>
#include "solucao.h"
#include "ctrabalho.h"

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


public:
    Widget(Solucao solucao = Solucao::SolucaoVazia(),QWidget *parent = 0);
    //~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QString Widget::gerarToolTip(cTrabalho trabalho);
    Solucao solucao;
    int tamanho_vertical; //definido pelo construtor
    int y_teto; //define distância entre topo do widget e o desenho do gráfico. é relativo às barras
    int escala;
    int posicao_zero; //define posição zero para o grafico de gantt

//private:
    //Ui::WidgetClass *ui;
};

#endif // WIDGET_H
