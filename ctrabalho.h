#ifndef CTRABALHO_H
#define CTRABALHO_H

#include <QTime>
#include <QString>
#include <QColor>
#include <QDate>
#include <QDateTime>

class cTrabalho{
    public:
        //cTrabalho(QTime inicio_, QTime fim_, QString coisa);
        cTrabalho(QTime inicio, QTime fim,QDate d_inicio, QDate d_fim,QString coisa, QColor ncor = QColor(0,0,0,255),bool overhead = false);
        cTrabalho();

        QDateTime getInicio(){return t_inicio;}
        QDateTime getFim(){return t_fim;}

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

        //float getFimFloat();

        bool getOverhead(){return overhead;}
        void setOverhead(bool overhead){this->overhead=overhead;}
        float getTamanho();

        QColor getCor(){return cor;}
        void setCor(QColor cor){this->cor=cor;}

//        QDate getDataInicio(){return d_inicio;}
        QDate getDataInicio(){return (QDate)t_inicio.date();}
//        QDate getDataFim(){return d_fim;}
        QDate getDataFim(){return (QDate)t_fim.date();}
//        void setDataInicio(QDate d_inicio){this->d_inicio=d_inicio;}
//        void setDataFim(QDate d_fim){this->d_fim=d_fim;}

    private:
        bool overhead;
//        QTime inicio;
//        QTime fim;
//        QDate d_inicio;
//        QDate d_fim;
        //int dia = 0;
        float posicao;
        int maquina;
        QDateTime t_inicio;
        QDateTime t_fim;
        QColor cor;
        QString texto, ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
};

#endif // CTRABALHO_H
