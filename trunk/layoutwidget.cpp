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
#include <QSignalMapper>
#include <QDateEdit>


layoutWidget::layoutWidget(Solucao solucao, QWidget *parent) : QWidget(parent){
    QScrollArea *scroll = new QScrollArea();
    QVBoxLayout *layout = new QVBoxLayout();

    QWidget *upper_field = new QWidget();
    QGridLayout *upper_layout = new QGridLayout();
    
    w = new Widget(solucao);
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    //QHBoxLayout *button_layout = new QHBoxLayout();

    set_hoje = new QPushButton("hoje");
    upper_layout->addWidget(set_hoje,0,0);
    set_hoje->show();

    date_previous = new QPushButton("anterior");
    //upper_layout->addWidget(date_previous,3,2);
    //button_layout->addWidget(date_previous);
    upper_layout->addWidget(date_previous,0,1);
    date_previous->show();

    //CustomDateEdit *d_edit = new CustomDateEdit();
    //d_edit = new CustomDateEdit();
    d_edit = new QDateEdit();
    upper_layout->addWidget(d_edit,0,2);
    d_edit->setDate(w->getDataAtual());
    d_edit->setCalendarPopup(true);
    d_edit->show();

    date_next = new QPushButton("próximo");
    //upper_layout->addWidget(date_next,3,2);
    //button_layout->addWidget(date_next);
    upper_layout->addWidget(date_next,0,3);
    date_next->show();

    zoom_plus = new QPushButton("zoom +");
    upper_layout->addWidget(zoom_plus,0,5);
    zoom_plus->setAutoRepeat(true);
    zoom_plus->show();

    zoom_minus = new QPushButton("zoom -");
    upper_layout->addWidget(zoom_minus,0,4);
    zoom_minus->setAutoRepeat(true);
    zoom_minus->show();

    //upper_layout->addLayout(button_layout,3,2);

    upper_field->setLayout(upper_layout);

    layout->addWidget(upper_field);
    layout->addWidget(scroll);
    //setFixedWidth(800);
    //setFixedHeight(600);

    setLayout(layout);

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
