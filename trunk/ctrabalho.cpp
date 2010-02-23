#include "ctrabalho.h"

cTrabalho::cTrabalho(QTime inicio, QTime fim, QString coisa, QColor cor, bool overhead){
    this->inicio = inicio;
    this->fim = fim;
    this->cor = cor;
    ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
    this->overhead = overhead;
}

float cTrabalho::getTamanho(){
    float t_inicio = inicio.hour()+inicio.minute()/60;
    float t_fim = fim.hour()+fim.minute()/60;
    return t_fim-t_inicio;
}

//cTrabalho::cTrabalho(){}

