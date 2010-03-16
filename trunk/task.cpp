#include "task.h"
#include <QDebug>

Task::Task(QTime inicio, QTime fim, QDate d_inicio, QDate d_fim, QString coisa, QColor cor, bool tempo_setup){
//    this->inicio = inicio;
//    this->fim = fim;
//    this->d_inicio = d_inicio;
//    this->d_fim = d_fim;
    this->cor = cor;
    texto = ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
    this->tempo_setup = tempo_setup;
    this->t_inicio = QDateTime(d_inicio,inicio);
    this->t_fim = QDateTime(d_fim,fim);
    this->posicao = 0;
    //this->maquina = 0;
}

float Task::getTamanho(){
    return (float)t_inicio.secsTo(t_fim)/(3600);
}

//float Task::getFimFloat(){
//    float h = t_fim.time().hour();
//    float m = t_fim.time().minute();
//    return h+(m/60);
//    //return fim.hour()+fim.minute()/60;
//}

//Task::Task(){}

