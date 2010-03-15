#include "layoutwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPalette>
#include <QGroupBox>
#include <QLabel>
#include <QLine>
#include <QPainter>
#include <QPushButton>
#include <QSignalMapper>
#include <QDateEdit>
#include <QGroupBox>


layoutWidget::layoutWidget(Solucao solucao, QWidget *parent) : QWidget(parent){
    QScrollArea *scroll = new QScrollArea();
    QVBoxLayout *layout = new QVBoxLayout();

    QWidget *upper_field = new QWidget();
    //QGridLayout *navegacao = new QGridLayout();
    QHBoxLayout *navegacao = new QHBoxLayout();
    
    w = new Widget(solucao);
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    //QHBoxLayout *button_layout = new QHBoxLayout();


    QGroupBox *date = new QGroupBox("data");
    QHBoxLayout *date_layout = new QHBoxLayout();


    set_hoje = new QPushButton("hoje");
    //navegacao->addWidget(set_hoje,0,0);
    //navegacao->addWidget(set_hoje);
    date_layout->addWidget(set_hoje);
    set_hoje->show();

    date_previous = new QPushButton("anterior");
    //navegacao->addWidget(date_previous,3,2);
    //button_layout->addWidget(date_previous);
    //navegacao->addWidget(date_previous,0,1);
    //navegacao->addWidget(date_previous);
    date_layout->addWidget(date_previous);
    date_previous->show();

    //CustomDateEdit *d_edit = new CustomDateEdit();
    //d_edit = new CustomDateEdit();
    d_edit = new QDateEdit();
    //navegacao->addWidget(d_edit,0,2);
    //navegacao->addWidget(d_edit);
    date_layout->addWidget(d_edit);
    d_edit->setDate(w->getDataAtual());
    d_edit->setCalendarPopup(true);
    d_edit->show();

    date_next = new QPushButton("próximo");
    //navegacao->addWidget(date_next,3,2);
    //button_layout->addWidget(date_next);
    //navegacao->addWidget(date_next,0,3);
    //navegacao->addWidget(date_next);
    date_layout->addWidget(date_next);
    date_next->show();

    date->setLayout(date_layout);
    navegacao->addWidget(date);

    QGroupBox *zoom = new QGroupBox("zoom");
    QHBoxLayout *zoom_layout = new QHBoxLayout();

    zoom_minus = new QPushButton("-");
    //navegacao->addWidget(zoom_minus,0,4);
    //navegacao->addWidget(zoom_minus);
    zoom_layout->addWidget(zoom_minus);
    zoom_minus->setAutoRepeat(true);
    zoom_minus->show();

    zoom_plus = new QPushButton("+");
    //navegacao->addWidget(zoom_plus,0,5);
    //navegacao->addWidget(zoom_plus);
    zoom_layout->addWidget(zoom_plus);
    zoom_plus->setAutoRepeat(true);
    zoom_plus->show();

    zoom->setLayout(zoom_layout);
    navegacao->addWidget(zoom);

    QGroupBox *interval = new QGroupBox("intervalo (horas)");
    QHBoxLayout *interval_layout = new QHBoxLayout();

    interval_layout->addWidget(new QLabel("início"));

    interval_begin = new QSpinBox();
    //navegacao->addWidget(interval_begin,0,5);
    //navegacao->addWidget(interval_begin);
    interval_layout->addWidget(interval_begin);
    interval_begin->setRange(0,24);
    interval_begin->setValue(w->getIntervaloInicio());
    interval_begin->show();

    interval_layout->addWidget(new QLabel("fim"));

    interval_end = new QSpinBox();
    //navegacao->addWidget(interval_end,0,6);
    //navegacao->addWidget(interval_end);
    interval_layout->addWidget(interval_end);
    interval_end->setRange(0,24);
    interval_end->setValue(w->getIntervaloFim());
    interval_end->show();

    interval->setLayout(interval_layout);
    navegacao->addWidget(interval);

    //navegacao->addLayout(button_layout,3,2);

    upper_field->setLayout(navegacao);

    layout->addWidget(upper_field);
    layout->addWidget(scroll);
    //setFixedWidth(800);
    //setFixedHeight(600);

    setLayout(layout);

    connect(interval_begin,SIGNAL(valueChanged(int)),w,SLOT(redrawIntervalBegin(int)));
    connect(interval_end,SIGNAL(valueChanged(int)),w,SLOT(redrawIntervalEnd(int)));

    QSignalMapper *sm_date = new QSignalMapper();
    sm_date->setMapping(date_previous,-1);
    sm_date->setMapping(date_next,1);
    sm_date->setMapping(set_hoje,0);
    connect(date_previous,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(date_next,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(set_hoje,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(sm_date,SIGNAL(mapped(int)),w,SLOT(redraw(int)));

    QSignalMapper *update_calendardate = new QSignalMapper();
    update_calendardate->setMapping(date_previous,-1);
    update_calendardate->setMapping(date_next,1);
    connect(date_previous,SIGNAL(clicked()),update_calendardate,SLOT(map()));
    connect(date_next,SIGNAL(clicked()),update_calendardate,SLOT(map()));
    connect(update_calendardate,SIGNAL(mapped(int)),this,SLOT(updateDateEdit(int)));
    //connect(update_calendardate,SIGNAL(mapped(QString)),this,SLOT(updateDateEdit(QString)));
    //connect(sm_date,SIGNAL(mapped(int)),this,SLOT(updateDateEdit(int)));

    QSignalMapper *sm_zoom = new QSignalMapper();
    sm_zoom->setMapping(zoom_plus,1);
    sm_zoom->setMapping(zoom_minus,-1);
    connect(zoom_plus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(zoom_minus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(sm_zoom,SIGNAL(mapped(int)),w,SLOT(redrawZoom(int)));

//    QSignalMapper *sm_date_edit_update = new QSignalMapper();
    /*
      * ARRUMAR OS BUGS DAQUI
      */
//    sm_date_edit_update->setMapping(date_next,w->getDataAtual().toString());
//    connect(date_next,SIGNAL(clicked()),sm_date_edit_update,SLOT(map()));
//    connect(sm_date_edit_update,SIGNAL(mapped(int)),this,SLOT(updateDateEdit(int)));

    //connect(date_next,SIGNAL(clicked()),d_edit,SLOT());

    //selecionar data pelo popup do calendário muda data exibida
    connect(d_edit,SIGNAL(dateChanged(QDate)),w,SLOT(redrawDate(QDate)));

    //connect(date_next,SIGNAL(clicked()),d_edit,SLOT(setDate(QDate::currentDate())));
    //connect(sm,SIGNAL(mapped(int)),w,SLOT(hide()));
}

void layoutWidget::updateDateEdit(int num){
    //qDebug() << "updateDateEdit called";
    //d_edit->setDate(w->getDataAtual().addDays(num));
    d_edit->setDate(w->getDataAtual());
}
