#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <QTime>
#include <QString>
#include <QList>
#include "ctrabalho.h"

class solucao{
    public:
    solucao();

    //QList<QList<cTrabalho> > getListaMaquinas(){return lista_maquinas;}
    //void setListaMaquinas(QList<QList<cTrabalho> > newlista){lista_maquinas=newlista;}

    static QList<QList<cTrabalho> > gerarSolucao();

    private:
    //QList<QList<cTrabalho> > lista_maquinas;
    //QList<cTrabalho> lista_trabalhos;
    //cTrabalho trabalho;
};

#endif // SOLUCAO_H
