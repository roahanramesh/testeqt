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


layoutWidget::layoutWidget(GanttScheduling scheduling, QWidget *parent) : QWidget(parent){
    QScrollArea *scroll = new QScrollArea();
    QVBoxLayout *layout = new QVBoxLayout();

    QWidget *upper_field = new QWidget();
    //QGridLayout *navegacao = new QGridLayout();
    QHBoxLayout *navegacao = new QHBoxLayout();
    navegacao->addStretch(1);
    
    this->scheduling = scheduling;
    w = new GanttChart(&(this->scheduling));
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    QGroupBox *date = new QGroupBox("data");
    QHBoxLayout *date_layout = new QHBoxLayout();
    QHBoxLayout *zoom_layout = new QHBoxLayout();

//    QPushButton *setsize = new QPushButton("random");
//    date_layout->addWidget(setsize);
//    setsize->setAutoRepeat(true);
    //setsize->show();

//    connect(setsize,SIGNAL(clicked()),this,SLOT(randomNum()));

    set_hoje = new QPushButton("hoje");
    date_layout->addWidget(set_hoje);

    date_previous = new QPushButton("anterior");
    date_layout->addWidget(date_previous);

    d_edit = new QDateEdit();
    date_layout->addWidget(d_edit);
    d_edit->setDate(w->getDataAtual());
    d_edit->setCalendarPopup(true);

    date_next = new QPushButton("próximo");
    date_layout->addWidget(date_next);

    date->setLayout(date_layout);
    navegacao->addWidget(date);

    QGroupBox *zoom = new QGroupBox("zoom");

    zoom_minus = new QPushButton("-");
    //navegacao->addWidget(zoom_minus,0,4);
    //navegacao->addWidget(zoom_minus);
    zoom_layout->addWidget(zoom_minus);
    zoom_minus->setAutoRepeat(true);
    //zoom_minus->show();

    zoom_plus = new QPushButton("+");
    //navegacao->addWidget(zoom_plus,0,5);
    //navegacao->addWidget(zoom_plus);
    zoom_layout->addWidget(zoom_plus);
    zoom_plus->setAutoRepeat(true);
    //zoom_plus->show();

    zoom->setLayout(zoom_layout);
    navegacao->addWidget(zoom);

    QGroupBox *interval = new QGroupBox("intervalo (horas)");
    QHBoxLayout *interval_layout = new QHBoxLayout();

    interval_layout->addWidget(new QLabel("início"));

    spinbox_begin = new QSpinBox();
//    navegacao->addWidget(spinbox_begin);
    interval_layout->addWidget(spinbox_begin);
    spinbox_begin->setRange(0,scheduling.getHoraInicio(w->getDataAtual()).hour());
    spinbox_begin->setValue(scheduling.getHoraInicio(w->getDataAtual()).hour());

    interval_layout->addWidget(new QLabel("fim"));

    spinbox_end = new QSpinBox();
//    navegacao->addWidget(spinbox_end);
    interval_layout->addWidget(spinbox_end);
    spinbox_end->setRange(scheduling.getHoraFinal(w->getDataAtual()).hour(),24);
    spinbox_end->setValue(scheduling.getHoraFinal(w->getDataAtual()).hour());

    interval->setLayout(interval_layout);
    navegacao->addWidget(interval);

    upper_field->setLayout(navegacao);

    layout->addWidget(upper_field);
    layout->addWidget(scroll);

    setLayout(layout);

    connect(spinbox_begin,SIGNAL(valueChanged(int)),w,SLOT(redrawIntervalBegin(int)));
    connect(spinbox_end,SIGNAL(valueChanged(int)),w,SLOT(redrawIntervalEnd(int)));

    QSignalMapper *sm_date = new QSignalMapper();
    sm_date->setMapping(date_previous,-1);
    sm_date->setMapping(date_next,1);
    sm_date->setMapping(set_hoje,0);
    connect(date_previous,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(date_next,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(set_hoje,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(sm_date,SIGNAL(mapped(int)),w,SLOT(redraw(int)));

    //atualiza faixa de valores permitidos nos spinboxes de ajuste do intervalo exibido
//    connect(date_previous,SIGNAL(clicked()),this,SLOT(updateIntervalRange()));
//    connect(date_next,SIGNAL(clicked()),this,SLOT(updateIntervalRange()));

    //botao 'hoje' atualiza d_edit
    connect(set_hoje,SIGNAL(clicked()),this,SLOT(updateDateEditToday()));
    //botao 'hoje' atualiza intervalo dos spinboxes
//    connect(set_hoje,SIGNAL(clicked()),this,SLOT(updateIntervalRange()));

//    QSignalMapper *update_calendardate = new QSignalMapper();
//    update_calendardate->setMapping(date_previous,-1);
//    update_calendardate->setMapping(date_next,1);
//    connect(date_previous,SIGNAL(clicked()),update_calendardate,SLOT(map()));
    connect(date_previous,SIGNAL(clicked()),this,SLOT(updateDateEdit()));
//    connect(date_previous,SIGNAL(clicked()),this,SLOT(updateSpinBox()));
//    connect(date_next,SIGNAL(clicked()),update_calendardate,SLOT(map()));
    connect(date_next,SIGNAL(clicked()),this,SLOT(updateDateEdit()));
//    connect(date_next,SIGNAL(clicked()),this,SLOT(updateSpinBox()));
//    connect(update_calendardate,SIGNAL(mapped(int)),this,SLOT(updateDateEdit(int)));
    //connect(update_calendardate,SIGNAL(mapped(QString)),this,SLOT(updateDateEdit(QString)));
    //connect(sm_date,SIGNAL(mapped(int)),this,SLOT(updateDateEdit(int)));

    QSignalMapper *sm_zoom = new QSignalMapper();
    sm_zoom->setMapping(zoom_plus,1);
    sm_zoom->setMapping(zoom_minus,-1);
    connect(zoom_plus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(zoom_minus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(sm_zoom,SIGNAL(mapped(int)),w,SLOT(redrawZoom(int)));

    //selecionar data pelo popup do calendário muda data exibida
    connect(d_edit,SIGNAL(dateChanged(QDate)),w,SLOT(redrawDate(QDate)));
//    connect(d_edit,SIGNAL(dateChanged(QDate)),this,SLOT(updateSpinBox()));

//    connect(date_next,SIGNAL(clicked()),d_edit,SLOT(setDate(QDate::currentDate())));
    //connect(sm,SIGNAL(mapped(int)),w,SLOT(hide()));
//    setFixedSize(800,600);
//    showMaximized();
//    qDebug() << layoutWidget::encodeDate(QDate::currentDate());
//    qDebug() << layoutWidget::teste(QDate::currentDate());
}

void layoutWidget::randomNum(int a, int b){
    qsrand(QTime::currentTime().msec());
    qDebug() << a+qrand()%(b-a);
//    qDebug() << "lol " << 2345%10 << 2345/10;
}

void layoutWidget::updateSpinBox(){
    updateIntervalRange(w->getIntervaloInicio(),w->getIntervaloFim());
}

void layoutWidget::updateIntervalRange(int begin, int end){
    spinbox_begin->setRange(0,begin);
    spinbox_begin->setValue(begin);
    spinbox_end->setRange(end,24);
    spinbox_end->setValue(end);
    //spinbox_begin->setRange(0,hora.hour());;
//    int begin = scheduling.getHoraInicio(w->getDataAtual()).hour();
//    spinbox_begin->setRange(0,begin>8?begin:8);
//    spinbox_begin->setValue(begin>8?begin:8);
//    int end = scheduling.getHoraFinal(w->getDataAtual()).hour();
//    spinbox_end->setRange(end,18>end?18:end);
//    spinbox_end->setValue(18>end?18:end);
//    w->setIntervaloFim(scheduling.getHoraFinal(w->getDataAtual()).hour());
//    w->setIntervaloInicio(scheduling.getHoraInicio(w->getDataAtual()).hour());
}

void layoutWidget::updateDateEdit(){
    //qDebug() << "updateDateEdit called";
    //d_edit->setDate(w->getDataAtual().addDays(num));
    d_edit->setDate(w->getDataAtual());
}

void layoutWidget::updateDateEditToday(){
    d_edit->setDate(QDate::currentDate());
}
