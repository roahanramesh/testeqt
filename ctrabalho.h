#ifndef CTRABALHO_H
#define CTRABALHO_H

#include <QTime>
#include <QString>

class cTrabalho{
    public:
        //cTrabalho(QTime inicio_, QTime fim_, QString coisa);
        cTrabalho(QTime in, QTime fi, QString coisa);
        cTrabalho();

        //getters e setters
        QTime getInicio(){return inicio;}
        void setInicio(QTime init){inicio = init;}
        QTime getFim(){return fim;}
        void setFim(QTime f){fim=f;}
        QString getOrdemProducao(){return ordem_producao;}
        void setOrdemProducao(QString op){ordem_producao = op;}
        QString getProduto(){return produto;}
        void setProduto(QString p){produto=p;}
        QString getAcabamento(){return acabamento;}
        void setAcabamento(QString a){acabamento=a;}
        QString getMaterialBase(){return material_base;}
        void setMaterialBase(QString mb){material_base=mb;}
        QString getQtdPecas(){return qtd_pecas;}
        void setQtdPecas(QString qtdp){qtd_pecas=qtdp;}
        QString getPilha(){return pilha;}
        void setPilha(QString p){pilha=p;}

    private:
        QTime inicio;
        QTime fim;
        QString ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
};

#endif // CTRABALHO_H
