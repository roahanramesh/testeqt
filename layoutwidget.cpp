#include "layoutwidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPalette>
#include <QGroupBox>


layoutWidget::layoutWidget(QWidget *parent) : QWidget(parent){
    QScrollArea *scroll = new QScrollArea();
    QVBoxLayout *layout = new QVBoxLayout();

    Widget *w = new Widget();
    scroll->setWidget(w);
    scroll->setBackgroundRole(QPalette::Light);

    layout->addWidget(scroll);

    //setFixedWidth(800);
    //setFixedHeight(600);

    setLayout(layout);
}

