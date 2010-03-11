#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <QTime>
#include <QString>
#include <QList>
#include "ctrabalho.h"
#include <QDebug>
#include <QFontMetrics>
#include <QDate>

class Solucao{
    public:
    Solucao();

    int get_max_x_size(){return max_x_size;}
    void set_max_x_size(int max_x_size){this->max_x_size=max_x_size;}
    int get_max_y_size(){return max_y_size;}
    void set_max_y_size(int max_y_size){this->max_y_size=max_y_size;}

    QList<QString> getNomeMaquinas(){return nome_maquinas;}
    void setNomeMaquinas(QList<QString> nome_maquinas){this->nome_maquinas=nome_maquinas;}

    QList<QList<cTrabalho> > getTrabalhos(){return trabalhos;}
    void setTrabalhos(QList<QList<cTrabalho> > trabalhos){this->trabalhos=trabalhos;}

    int getMaiorNomeMaquina();

    static Solucao GerarSolucao();
    static Solucao SolucaoVazia();
    static Solucao GerarSolucao2();

    //retorna a maior duração entre todos os trabalhos, utilizado para definir até onde que se deve desenhar a linha do tempo
    int getDiasDuracao();

    QDate getDataInicio(); //retorna a menor data dentre os trabalhos
    QDate getDataFinal(); //retorna a maior data dentre os trabalhos
    int getDiasTrabalho(cTrabalho trabalho); //retorna offset de dias de um trabalho
    float getCoordTrabalho(cTrabalho trabalho); //retorna coordenada x onde o trabalho deve ser desenhado

    QList<QList<cTrabalho> > prepararSolucao(int dia = 1);

    void debugarSolucao();

    //getDataTrabalho necessário pra funcionalidade de rescheduling
    //QDateTime getDataTrabalho(cTrabalho trabalho){} //retorna tempo inicial do trabalho a partir da sua coordenada

    //QList<dataSolucao> getListaSolucao(){return lista_solucao;}
    //void setListaSolucao(QList<dataSolucao> lista_solucao){this->lista_solucao = lista_solucao;}
    int getEscala(){return escala;}
    void setEscala(int escala){this->escala=escala;}

    private:
    //variável que define a escala do gráfico
    int escala;

    QList<QList<cTrabalho> > trabalhos;
    QList<QString> nome_maquinas;

    //QList<celulaTrabalho> lista_solucao;

    int max_x_size;
    int max_y_size;

};

struct dataCelula{
    QDate data;
    QList<cTrabalho> trabalhos;
};

struct celulaTrabalho{
    QString nome;
    QList<dataCelula> dia;
};
#endif // SOLUCAO_H
