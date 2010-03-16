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

    QList<QString> getNomeCelulasTrabalho(){return nome_celulas_trabalho;}
    void setNomeCelulasTrabalho(QList<QString> nome_celulas_trabalho){this->nome_celulas_trabalho=nome_celulas_trabalho;}

    QList<QList<Task> > getTasks(){return tasks;}
    void setTasks(QList<QList<Task> > tasks){this->tasks=tasks;}

    int getMaiorNomeCelulaTrabalho();

    static Scheduling GerarScheduling();
    static Scheduling SchedulingVazia();
//    static Scheduling GerarScheduling2();

    //retorna a maior duração entre todos os tasks, utilizado para definir até onde que se deve desenhar a linha do tempo
    int getDiasDuracao();

    QDate getDataInicio(); //retorna a menor data dentre os tasks
    QDate getDataFinal(); //retorna a maior data dentre os tasks
    int getDiasTask(Task task); //retorna offset de dias de um trabalho
    float getCoordTask(Task task); //retorna coordenada x onde o trabalho deve ser desenhado

    void debugarScheduling();

    //getDataTrabalho necessário pra funcionalidade de rescheduling
    //QDateTime getDataTrabalho(Task trabalho){} //retorna tempo inicial do trabalho a partir da sua coordenada

    //QList<dataSolucao> getListaSolucao(){return lista_scheduling;}
    //void setListaSolucao(QList<dataSolucao> lista_scheduling){this->lista_scheduling = lista_scheduling;}
    int getEscala(){return escala;}
    void setEscala(int escala){this->escala=escala;}

    private:
    //variável que define a escala do gráfico
    int escala;

    QList<QList<Task> > tasks;
    QList<QString> nome_celulas_trabalho;

    //QList<celulaTrabalho> lista_scheduling;

    int max_x_size;
    int max_y_size;

};

#endif // SOLUCAO_H
