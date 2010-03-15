#pragma once
#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QWidget>
#include "widget.h"
#include "solucao.h"
#include <QDateEdit>
#include <QPushButton>

class layoutWidget : public QWidget
{
    Q_OBJECT
    public:
        layoutWidget(Solucao so = Solucao::SolucaoVazia(), QWidget *parent = 0);
    public slots:
        //void updateDateEdit(QString date){d_edit->setDate(QDate::fromString(date));}
        void updateDateEdit(int num);
    private:
        QDateEdit *d_edit;
        Widget *w;
        QPushButton *set_hoje;
        QPushButton *date_previous;
        QPushButton *date_next;
        QPushButton *zoom_plus;
        QPushButton *zoom_minus;
};

#endif // LAYOUTWIDGET_H
