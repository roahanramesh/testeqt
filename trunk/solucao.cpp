#include "solucao.h"
#include <QDebug>

Solucao::Solucao(){
    makespan = 1;
    maior_atraso = 0;
    num_op_atrasadas = 0;
    total_atrasos = 0;
    custo_mao_de_obra = 0;
    custos_operacionais = 0;
    total_setup = 0;
    total_ociosidade = 0;
    total_folga = 0;

    trabalhos = SolucaoVazia();

    escala = 50;
}

int Solucao::CalculateX(Solucao solucao){
    QList<QList<cTrabalho> > listasolucao = solucao.GerarSolucao();
    QList<int> listalargura;
    int tamanho=0;
    foreach(QList<cTrabalho> trabalhos, listasolucao){
          tamanho = trabalhos.last().getInicioFloat()*solucao.get_escala()+trabalhos.last().getFimFloat()-trabalhos.last().getInicioFloat()*solucao.get_escala();
//        foreach(cTrabalho trabalho, trabalhos){
//            largura += trabalho.getFimFloat()-trabalho.getInicioFloat();
//        }
          listalargura.append(tamanho);
//        largura = 0;
    }
    qSort(listalargura);
    //return listalargura.last();//*solucao.get_escala();
    return 5000;
}

int Solucao::CalculateY(){
    return 400;
}

QList<QList<cTrabalho> > Solucao::SolucaoVazia(){
    cTrabalho t(QTime(0,0),QTime(0,0),"",QColor(0,0,0,0));
    QList<cTrabalho> l;
    l.append(t);
    QList<QList<cTrabalho> > s;
    s.append(l);
    return s;
}

QList<QList<cTrabalho> > Solucao::GerarSolucao(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    cTrabalho t1_1(QTime(1,0),QTime(2,30),"t1_1",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t1_2(QTime(3,30),QTime(5,10),"t1_2",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t1_3(QTime(6,0),QTime(8,0),"t1_3",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t1_4(QTime(8,0),QTime(10,0),"t1_4",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t1_5(QTime(15,0),QTime(18,0),"t1_5",QColor(qrand()%255,qrand()%255,qrand()%255,200));

    cTrabalho t2_0(QTime(0,0), QTime(1,0), "t2_0",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t2_1(QTime(6,0), QTime(12,0), "t2_1",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t2_2(QTime(12,0), QTime(15,0), "t2_2",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t2_3(QTime(15,0), QTime(18,0), "t2_3",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t2_4(QTime(19,0), QTime(22,0), "t2_3",QColor(qrand()%255,qrand()%255,qrand()%255,200));

    cTrabalho t3_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t3_2(QTime(5,0), QTime(6,0), "t3_2",QColor(qrand()%255,qrand()%255,qrand()%255,200));
    cTrabalho t3_3(QTime(8,0), QTime(10,0), "t3_3",QColor(qrand()%255,qrand()%255,qrand()%255,200));

    QList<cTrabalho> l1;
    l1.append(t1_1);
    l1.append(t1_2);
    l1.append(t1_3);
    l1.append(t1_4);
    l1.append(t1_5);

    QList<cTrabalho> l2;
    l2.append(t2_0);
    l2.append(t2_1);
    l2.append(t2_2);
    l2.append(t2_3);
    l2.append(t2_4);

    QList<cTrabalho> l3;
    l3.append(t3_1);
    l3.append(t3_2);
    l3.append(t3_3);

    QList<QList<cTrabalho> > nsolucao;
    nsolucao.append(l1);
    nsolucao.append(l2);
    nsolucao.append(l3);

    return nsolucao;
}