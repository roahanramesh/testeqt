#include "ctrabalho.h"
#include <QDebug>

cTrabalho::cTrabalho(QTime inicio, QTime fim, QDate d_inicio, QDate d_fim, QString coisa, QColor cor, bool overhead){
//    this->inicio = inicio;
//    this->fim = fim;
//    this->d_inicio = d_inicio;
//    this->d_fim = d_fim;
    this->cor = cor;
    texto = ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
    this->overhead = overhead;
    this->t_inicio = QDateTime(d_inicio,inicio);
    this->t_fim = QDateTime(d_fim,fim);
}

float cTrabalho::getTamanho(){
//    float h_inicio = inicio.hour();
//    float m_inicio = inicio.minute();
//    float h_fim = fim.hour();
//    float m_fim = fim.minute();
//    float inicio_total = h_inicio+(m_inicio/60);
//    float fim_total = h_fim+(m_fim/60);
    //QDateTime dt_inicio = QDateTime(d_inicio,inicio);
    //QDateTime dt_fim = QDateTime(d_fim,fim);
    //qDebug() << QString::number(fim_total-inicio_total) << " vs " <<QString::number((float)inicio.secsTo(fim)/(60*60));
//    QDateTime dt1 = QDateTime(QDate(10,3,2),QTime(12,0,0,0));
//    QDateTime dt2 = QDateTime(QDate(10,3,3),QTime(18,0,0,0));
    //qDebug() << QString::number(fim_total-inicio_total) << " vs " << QString::number((float)dt_inicio.secsTo(dt_fim)/(60*60));
    //return fim_total-inicio_total;
    return (float)t_inicio.secsTo(t_fim)/(3600);
}

/*
 * CORRIGIR ESTE MÉTODO!
 */
float cTrabalho::getCoordenadaInicio(QDate solucao_inicio){
    //int dias = solucao_inicio.daysTo(t_inicio.date());
    float h = t_inicio.time().hour();
    float m = t_inicio.time().minute();
    //qDebug() << "(ctrabalho.cpp) dias " << dias << " valor retornado:original" << QString::number((dias+1)*h+(m/60)) << " " << QString::number(h+(m/60));
    //qDebug() << "ctrabalho.h " <<(h+(m/60));
    return (h+(m/60));
    //return inicio.hour()+inicio.minute()/60;
}

//float cTrabalho::getFimFloat(){
//    float h = t_fim.time().hour();
//    float m = t_fim.time().minute();
//    return h+(m/60);
//    //return fim.hour()+fim.minute()/60;
//}

//cTrabalho::cTrabalho(){}

