#ifndef TASK_H
#define TASK_H

#include <QTime>
#include <QString>
#include <QColor>
#include <QDate>
#include <QDateTime>

//class Task{
class Task{
    public:
        Task(QTime inicio, QTime fim,QDate d_inicio, QDate d_fim,QString coisa, QColor ncor = QColor(0,0,0,255),bool tempo_setup = false);
        Task();

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

        bool getTempoSetup(){return tempo_setup;} //TRUE se for tempo de setup ao invés de trabalho
        void setTempoSetup(bool tempo_setup){this->tempo_setup=tempo_setup;}
        float getTamanho();

        QColor getCor(){return cor;}
        void setCor(QColor cor){this->cor=cor;}

        QDate getDataInicio(){return (QDate)t_inicio.date();}
        QDate getDataFim(){return (QDate)t_fim.date();}

    private:
        bool tempo_setup;
        float posicao;
        int maquina;
        QDateTime t_inicio;
        QDateTime t_fim;
        QColor cor;
        QString texto, ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
};

#endif // TASK_H
