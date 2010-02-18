#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <QTime>
#include <QString>
#include <QList>
#include "ctrabalho.h"

class Solucao{
    public:
    Solucao();

    float get_makespan(){return makespan;}
    void set_makespan(int makespan){this->makespan=makespan;}
    float get_maior_atraso(){return maior_atraso;}
    void set_maior_atraso(int maior_atraso){this->maior_atraso=maior_atraso;}
    float get_num_op_atrasadas(){return num_op_atrasadas;}
    void set_num_op_atrasadas(int num_op_atrasadas){this->num_op_atrasadas=num_op_atrasadas;}
    float get_total_atrasos(){return total_atrasos;}
    void set_total_atrasos(int total_atrasos){this->total_atrasos=total_atrasos;}
    float get_custo_mao_de_obra(){return custo_mao_de_obra;}
    void set_custo_mao_de_obra(int custo_mao_de_obra){this->custo_mao_de_obra=custo_mao_de_obra;}
    float get_custos_operacionais(){return custos_operacionais;}
    void set_custos_operacionais(int custos_operacionais){this->custos_operacionais=custos_operacionais;}
    float get_total_setup(){return total_setup;}
    void set_total_setup(int total_setup){this->total_setup=total_setup;}
    float get_total_ociosidade(){return total_ociosidade;}
    void set_total_ociosidade(int total_ociosidade){this->total_ociosidade=total_ociosidade;}
    float get_total_folga(){return total_folga;}
    void set_total_folga(int total_folga){this->total_folga=total_folga;}

    int get_max_x_size(){return max_x_size;}
    void set_max_x_size(int max_x_size){this->max_x_size=max_x_size;}
    int get_max_y_size(){return max_y_size;}
    void set_max_y_size(int max_y_size){this->max_y_size=max_y_size;}

    int get_escala(){return escala;}

    static QList<QList<cTrabalho> > GerarSolucao();
    static QList<QList<cTrabalho> > SolucaoVazia();

        /*TODO*/
    int CalculateX();
    int CalculateY();

    private:

    //variável que define a escala do gráfico
    int escala;

    float makespan;
    float maior_atraso;
    float num_op_atrasadas;
    float total_atrasos;
    float custo_mao_de_obra;
    float custos_operacionais;
    float total_setup;
    float total_ociosidade;
    float total_folga;
    QList<QList<cTrabalho> > trabalhos;

    int max_x_size;
    int max_y_size;

};

#endif // SOLUCAO_H
