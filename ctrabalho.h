#ifndef CTRABALHO_H
#define CTRABALHO_H

#include <QTime>
#include <QString>
#include <QColor>

class cTrabalho{
    public:
        //cTrabalho(QTime inicio_, QTime fim_, QString coisa);
        cTrabalho(QTime inicio, QTime fim, QString coisa, QColor ncor = QColor(0,0,0,255),bool overhead = false);
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
        QString getTexto(){return texto;}
        void setText(QString texto){this->texto=texto;}

        float getInicioFloat();
        float getFimFloat();

        bool getOverhead(){return overhead;}
        void setOverhead(bool overhead){this->overhead=overhead;}
        float getTamanho();

        QColor getCor(){return cor;}
        void setCor(QColor cor){this->cor=cor;}

    private:
        bool overhead;
        QTime inicio;
        QTime fim;
        QColor cor;
        QString texto, ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
};

#endif // CTRABALHO_H
