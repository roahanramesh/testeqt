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
    
    Widget *w = new Widget(solucao);
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    //QHBoxLayout *button_layout = new QHBoxLayout();

    QPushButton *hoje = new QPushButton("hoje");
    upper_layout->addWidget(hoje,0,0);
    hoje->show();

    QPushButton *b1 = new QPushButton("anterior");
    //upper_layout->addWidget(b1,3,2);
    //button_layout->addWidget(b1);
    upper_layout->addWidget(b1,0,1);
    b1->show();

    QDateEdit *d_edit = new QDateEdit();
    upper_layout->addWidget(d_edit,0,2);
    d_edit->setCalendarPopup(true);
    d_edit->show();

    QPushButton *b2 = new QPushButton("próximo");
    //upper_layout->addWidget(b2,3,2);
    //button_layout->addWidget(b2);
    upper_layout->addWidget(b2,0,3);
    b2->show();

    QPushButton *zoomplus = new QPushButton("zoom +");
    upper_layout->addWidget(zoomplus,0,5);
    zoomplus->show();

    QPushButton *zoomminus = new QPushButton("zoom -");
    upper_layout->addWidget(zoomminus,0,4);
    zoomminus->show();

    //upper_layout->addLayout(button_layout,3,2);

    upper_field->setLayout(upper_layout);

    layout->addWidget(upper_field);
    layout->addWidget(scroll);
    //setFixedWidth(800);
    //setFixedHeight(600);

    setLayout(layout);

    QSignalMapper *sm_date = new QSignalMapper();
    sm_date->setMapping(b1,-1);
    sm_date->setMapping(b2,1);
    connect(b1,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(b2,SIGNAL(clicked()),sm_date,SLOT(map()));
    connect(sm_date,SIGNAL(mapped(int)),w,SLOT(redraw(int)));

    QSignalMapper *sm_zoom = new QSignalMapper();
    sm_zoom->setMapping(zoomplus,1);
    sm_zoom->setMapping(zoomminus,-1);
    connect(zoomplus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(zoomminus,SIGNAL(clicked()),sm_zoom,SLOT(map()));
    connect(sm_zoom,SIGNAL(mapped(int)),w,SLOT(redrawZoom(int)));
    //connect(sm,SIGNAL(mapped(int)),w,SLOT(hide()));
}

