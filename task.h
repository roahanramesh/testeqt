#ifndef TASK_H
#define TASK_H

#include <QTime>
#include <QString>
#include <QColor>
#include <QDate>
#include <QDateTime>

//class Task{

//! Class representing a task
/*!
  The Task class has information about a particular class within the scheduling. It is associated to a workcell and a date/time.
  */
class Task{
    public:
    //! Class constructor
    /*!
      Takes several arguments to construct a complete Task object.
      */
        Task(QTime inicio, QTime fim,QDate d_inicio, QDate d_fim,QString coisa, QColor ncor = QColor(0,0,0,255),bool tempo_setup = false);
        Task();

        QDateTime getInicio(){return t_inicio;}
        void setInicio(QDateTime t_inicio){this->t_inicio=t_inicio;}
        QDateTime getFim(){return t_fim;}
        void setFim(QDateTime t_fim){this->t_fim=t_fim;}

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

        bool getTempoSetup(){return tempo_setup;} //TRUE se for tempo de setup ao inv�s de trabalho
        void setTempoSetup(bool tempo_setup){this->tempo_setup=tempo_setup;}
        float getTamanho();
        float getPosicao(){return posicao;}
        void setPosicao(float posicao){this->posicao=posicao;}

        QColor getCor(){return cor;}
        void setCor(QColor cor){this->cor=cor;}

        QDate getDataInicio(){return (QDate)t_inicio.date();}
        QDate getDataFim(){return (QDate)t_fim.date();}

    private:
        bool tempo_setup;
        float posicao;
        //int maquina;
        QDateTime t_inicio;
        QDateTime t_fim;
        QColor cor;
        QString texto, ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
};

//QDataStream &operator<<(QDataStream &stream, Task &task){
//    stream << task.getTempoSetup();
//    stream << task.getPosicao();
//    stream << task.getDataInicio();
//    stream << task.getDataFim();
//    stream << task.getCor();
//    stream << task.getTexto();
//    stream << task.getOrdemProducao();
//    stream << task.getProduto();
//    stream << task.getAcabamento();
//    stream << task.getMaterialBase();
//    stream << task.getQtdPecas();
//    stream << task.getPilha();
//    return stream;
//    //stream << task.maquina
//}
//
//QDataStream &operator>>(QDataStream &stream, Task &task){
//    bool tempo_setup;
//    stream >> tempo_setup;
//    task.setTempoSetup(tempo_setup);
//    float posicao;
//    stream >> posicao;
//    task.setPosicao(posicao);
//    QDateTime data;
//    stream >> data;
//    task.setInicio(data);
//    stream >> data;
//    task.setFim(data);
//    QColor cor;
//    stream >> cor;
//    task.setCor(cor);
//    QString aux;
//    stream >> aux;
//    task.setText(aux);
//    stream >> aux;
//    task.setOrdemProducao(aux);
//    stream >> aux;
//    task.setProduto(aux);
//    stream >> aux;
//    task.setAcabamento(aux);
//    stream >> aux;
//    task.setMaterialBase(aux);
//    stream >> aux;
//    task.setQtdPecas(aux);
//    stream >> aux;
//    task.setPilha(aux);
//    return stream;
//    //return task;
////QString texto, ordem_producao, produto, acabamento, material_base, qtd_pecas, pilha;
//}

#endif // TASK_H
