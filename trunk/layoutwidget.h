#pragma once
#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QWidget>
#include "widget.h"
#include "solucao.h"
#include <QDateEdit>

class layoutWidget : public QWidget
{
    Q_OBJECT
    public:
        layoutWidget(Solucao so = Solucao::SolucaoVazia(), QWidget *parent = 0);
};

class CustomDateEdit : public QDateEdit
{
    Q_OBJECT
    public slots:
        void setNewDate(QString newdate){this->setDate(QDate::fromString(newdate));qDebug()<<"WAT";}
};
#endif // LAYOUTWIDGET_H
