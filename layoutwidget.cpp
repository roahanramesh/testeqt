#include "layoutwidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPalette>
#include <QGroupBox>
#include <QLabel>
#include <QLine>
#include <QPainter>
#include <QPushButton>


layoutWidget::layoutWidget(Solucao solucao, QWidget *parent) : QWidget(parent){
    QScrollArea *scroll = new QScrollArea();
    QVBoxLayout *layout = new QVBoxLayout();
    QString string;

    QWidget *upper_field = new QWidget();
    QGridLayout *upper_layout = new QGridLayout();
    //labels do topo
    string = "Makespan : "+QString::number(solucao.getMakespan())+" hora"+(solucao.getMakespan()!=1?"s":"");
    QLabel *makespan_label = new QLabel(string);
    upper_layout->addWidget(makespan_label,0,0);
    makespan_label->show();

    string = "Maior atraso : "+QString::number(solucao.getMaiorAtraso())+" hora"+(solucao.getMaiorAtraso()!=1?"s":"");
    QLabel *maioratraso_label = new QLabel(string);
    upper_layout->addWidget(maioratraso_label,1,0);
    maioratraso_label->show();

    string = "Numero de Ops atrasadas : "+QString::number(solucao.getNumOpsAtrasadas());
    QLabel *opatrasadas_label = new QLabel(string);
    upper_layout->addWidget(opatrasadas_label,2,0);
    opatrasadas_label->show();

    string = "Total atrasos : "+QString::number(solucao.getTotalAtrasos())+" hora"+(solucao.getTotalAtrasos()!=1?"s":"");
    QLabel *total_atrasos_label = new QLabel(string);
    upper_layout->addWidget(total_atrasos_label,0,1);
    total_atrasos_label->show();

    string = "Custo mão de obra : R$"+QString::number(solucao.getCustoMaoDeObra());
    QLabel *get_custo_mao_de_obra = new QLabel(string);
    upper_layout->addWidget(get_custo_mao_de_obra,1,1);
    get_custo_mao_de_obra->show();

    string = "Custos operacionais : R$"+QString::number(solucao.getCustosOperacionais());
    QLabel *get_custos_operacionais = new QLabel(string);
    upper_layout->addWidget(get_custos_operacionais,2,1);
    get_custos_operacionais->show();

    string = "Total setup : "+QString::number(solucao.getTotalSetup())+" hora"+(solucao.getTotalSetup()!=1?"s":"");
    QLabel *get_total_setup = new QLabel(string);
    upper_layout->addWidget(get_total_setup,0,2);
    get_total_setup->show();

    string = "Total ociosidade : "+QString::number(solucao.getTotalOciosidade())+" hora"+(solucao.getTotalOciosidade()!=1?"s":"");
    QLabel *get_total_ociosidade = new QLabel(string);
    upper_layout->addWidget(get_total_ociosidade,1,2);
    get_total_ociosidade->show();

    string = "Total folga : "+QString::number(solucao.getTotalFolga())+" hora"+(solucao.getTotalFolga()!=1?"s":"");
    QLabel *get_total_folga = new QLabel(string);
    upper_layout->addWidget(get_total_folga,2,2);
    get_total_folga->show();

    QPushButton *b1 = new QPushButton("b1");
    upper_layout->addWidget(b1,3,2);
    b1->show();

    upper_field->setLayout(upper_layout);


    Widget *w = new Widget(solucao);
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    layout->addWidget(upper_field);
    layout->addWidget(scroll);
    //setFixedWidth(800);
    //setFixedHeight(600);

    setLayout(layout);
    connect(b1,SIGNAL(clicked()),w,SLOT(hide()));
}

