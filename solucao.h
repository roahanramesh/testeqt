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

    float getMakespan(){return makespan;}
    void setMakespan(int makespan){this->makespan=makespan;}
    float getMaiorAtraso(){return maior_atraso;}
    void setMaiorAtraso(int maior_atraso){this->maior_atraso=maior_atraso;}
    float getNumOpsAtrasadas(){return num_op_atrasadas;}
    void setNumOpsAtrasadas(int num_op_atrasadas){this->num_op_atrasadas=num_op_atrasadas;}
    float getTotalAtrasos(){return total_atrasos;}
    void setTotalAtrasos(int total_atrasos){this->total_atrasos=total_atrasos;}
    float getCustoMaoDeObra(){return custo_mao_de_obra;}
    void setCustoMaoDeObra(int custo_mao_de_obra){this->custo_mao_de_obra=custo_mao_de_obra;}
    float getCustosOperacionais(){return custos_operacionais;}
    void setCustosOperacionais(int custos_operacionais){this->custos_operacionais=custos_operacionais;}
    float getTotalSetup(){return total_setup;}
    void setTotalSetup(int total_setup){this->total_setup=total_setup;}
    float getTotalOciosidade(){return total_ociosidade;}
    void setTotalOciosidade(int total_ociosidade){this->total_ociosidade=total_ociosidade;}
    float getTotalFolga(){return total_folga;}
    void setTotalFolga(int total_folga){this->total_folga=total_folga;}

    int get_max_x_size(){return max_x_size;}
    void set_max_x_size(int max_x_size){this->max_x_size=max_x_size;}
    int get_max_y_size(){return max_y_size;}
    void set_max_y_size(int max_y_size){this->max_y_size=max_y_size;}

    int getEscala(){return escala;}

    QList<QString> getNomeMaquinas(){return nome_maquinas;}
    void setNomeMaquinas(QList<QString> nome_maquinas){this->nome_maquinas=nome_maquinas;}

    QList<QList<cTrabalho> > getTrabalhos(){return trabalhos;}
    void setTrabalhos(QList<QList<cTrabalho> > trabalhos){this->trabalhos=trabalhos;}

    int getMaiorNomeMaquina();

    //static QList<QList<cTrabalho> > GerarSolucao();
    static Solucao GerarSolucao();
    //static QList<QList<cTrabalho> > SolucaoVazia();
    static Solucao SolucaoVazia();

    //retorna a maior duração entre todos os trabalhos, utilizado para definir até onde que se deve desenhar a linha do tempo
    int getDiasDuracao();

    QDate getDataInicio(); //retorna a menor data dentre os trabalhos
    QDate getDataFinal(); //retorna a maior data dentre os trabalhos
    int getDiasTrabalho(cTrabalho trabalho); //retorna offset de dias de um trabalho

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
    QList<QString> nome_maquinas;

    int max_x_size;
    int max_y_size;

};

#endif // SOLUCAO_H
