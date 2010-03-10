#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QWidget>
#include "widget.h"
#include "solucao.h"

class layoutWidget : public QWidget
{
    Q_OBJECT
    public:
        layoutWidget(Solucao so = Solucao::SolucaoVazia(), QWidget *parent = 0);
};

#endif // LAYOUTWIDGET_H
