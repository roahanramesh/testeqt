#include "ctrabalho.h"

cTrabalho::cTrabalho(QTime inicio, QTime fim, QString coisa, QColor cor, bool overhead){
    this->inicio = inicio;
    this->fim = fim;
    this->cor = cor;
    texto = ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
    this->overhead = overhead;
}

float cTrabalho::getTamanho(){
    float h_inicio = inicio.hour();
    float m_inicio = inicio.minute();
    float h_fim = fim.hour();
    float m_fim = fim.minute();
    float inicio_total = h_inicio+(m_inicio/60);
    float fim_total = h_fim+(m_fim/60);
    return fim_total-inicio_total;
}

float cTrabalho::getInicioFloat(){
    float h = inicio.hour();
    float m = inicio.minute();
    return h+(m/60);
    //return inicio.hour()+inicio.minute()/60;
}

float cTrabalho::getFimFloat(){
    float h = fim.hour();
    float m = fim.minute();
    return h+(m/60);
    //return fim.hour()+fim.minute()/60;
}

//cTrabalho::cTrabalho(){}

