#pragma once
#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QWidget>
#include "ganttchart.h"
#include "ganttscheduling.h"
#include <QDateEdit>
#include <QPushButton>
#include <QSpinBox>

class layoutWidget : public QWidget
{
    Q_OBJECT
    public:
        layoutWidget(GanttScheduling so = GanttScheduling::GanttSchedulingVazia(), QWidget *parent = 0);
    public slots:
        //void updateDateEdit(QString date){d_edit->setDate(QDate::fromString(date));}
        void updateDateEdit(QDate date);
        void updateDateEditToday();
        void updateIntervalRange();
        void randomNum(int a=8, int b=22);
//        static bool teste(QDate t);
    private:
        GanttScheduling scheduling;
        QDateEdit *d_edit;
        GanttChart *w;
        QPushButton *set_hoje;
        QPushButton *date_previous;
        QPushButton *date_next;
        QPushButton *zoom_plus;
        QPushButton *zoom_minus;
//        QSpinBox *spinbox_begin;
//        QSpinBox *spinbox_end;
};

#endif // LAYOUTWIDGET_H
