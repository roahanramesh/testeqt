#include "ctrabalho.h"

cTrabalho::cTrabalho(QTime in, QTime fi, QString coisa){
    inicio = in;
    fim = fi;
    ordem_producao = acabamento = produto = material_base = qtd_pecas = pilha = coisa;
}

cTrabalho::cTrabalho(){}

