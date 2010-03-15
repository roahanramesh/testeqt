#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <QTime>
#include <QString>
#include <QList>
#include "task.h"
#include <QDebug>
#include <QFontMetrics>
#include <QDate>

class Scheduling{
    public:
    Scheduling();

    int get_max_x_size(){return max_x_size;}
    void set_max_x_size(int max_x_size){this->max_x_size=max_x_size;}
    int get_max_y_size(){return max_y_size;}
    void set_max_y_size(int max_y_size){this->max_y_size=max_y_size;}

    QList<QString> getNomeMaquinas(){return nome_maquinas;}
    void setNomeMaquinas(QList<QString> nome_maquinas){this->nome_maquinas=nome_maquinas;}

    QList<QList<Task> > getTrabalhos(){return trabalhos;}
    void setTrabalhos(QList<QList<Task> > trabalhos){this->trabalhos=trabalhos;}

    int getMaiorNomeMaquina();

    static Scheduling GerarScheduling();
    static Scheduling SchedulingVazia();
//    static Scheduling GerarScheduling2();

    //retorna a maior duração entre todos os trabalhos, utilizado para definir até onde que se deve desenhar a linha do tempo
    int getDiasDuracao();

    QDate getDataInicio(); //retorna a menor data dentre os trabalhos
    QDate getDataFinal(); //retorna a maior data dentre os trabalhos
    int getDiasTrabalho(Task trabalho); //retorna offset de dias de um trabalho
    float getCoordTrabalho(Task trabalho); //retorna coordenada x onde o trabalho deve ser desenhado

    void debugarScheduling();

    //getDataTrabalho necessário pra funcionalidade de rescheduling
    //QDateTime getDataTrabalho(Task trabalho){} //retorna tempo inicial do trabalho a partir da sua coordenada

    //QList<dataSolucao> getListaSolucao(){return lista_solucao;}
    //void setListaSolucao(QList<dataSolucao> lista_solucao){this->lista_solucao = lista_solucao;}
    int getEscala(){return escala;}
    void setEscala(int escala){this->escala=escala;}

    private:
    //variável que define a escala do gráfico
    int escala;

    QList<QList<Task> > trabalhos;
    QList<QString> nome_maquinas;

    //QList<celulaTrabalho> lista_solucao;

    int max_x_size;
    int max_y_size;

};

struct dataCelula{
    QDate data;
    QList<Task> trabalhos;
};

struct celulaTrabalho{
    QString nome;
    QList<dataCelula> dia;
};
#endif // SOLUCAO_H
