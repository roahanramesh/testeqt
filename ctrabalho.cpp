#include "ctrabalho.h"

cTrabalho::cTrabalho(QTime in, QTime fi, QString coisa, QColor ncor){
    inicio = in;
    fim = fi;
    cor = ncor;
    ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
}

cTrabalho::cTrabalho(){}

