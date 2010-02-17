#include "solucao.h"

solucao::solucao(){

}

QList<QList<cTrabalho> > solucao::gerarSolucao(){
    cTrabalho t1_1(QTime(1,0),QTime(3,0),"t1_1");
    cTrabalho t1_2(QTime(3,0),QTime(5,0),"t1_2");
    cTrabalho t1_3(QTime(5,0),QTime(8,0),"t1_3");
    cTrabalho t1_4(QTime(8,0),QTime(10,0),"t1_4");
    cTrabalho t1_5(QTime(15,0),QTime(18,0),"t1_5");

//    cTrabalho t2_1(QTime(6,0), QTime(12,0), "t2_1");
//    cTrabalho t2_2(QTime(12,0), QTime(15,0), "t2_2");
//    cTrabalho t2_3(QTime(15,0), QTime(18,0), "t2_3");
//
//    cTrabalho t3_1(QTime(3,0), QTime(4,0), "t3_1");
//    cTrabalho t3_2(QTime(5,0), QTime(6,0), "t3_2");
//    cTrabalho t3_3(QTime(8,0), QTime(10,0), "t3_3");

    QList<cTrabalho> l1;
    l1.append(t1_1);
    l1.append(t1_2);
    l1.append(t1_3);
    l1.append(t1_4);
    l1.append(t1_5);

//    QList<cTrabalho> l2;
//    l2.append(t2_1);
//    l2.append(t2_2);
//    l2.append(t2_3);
//
//    QList<cTrabalho> l3;
//    l3.append(t3_1);
//    l3.append(t3_2);
//    l3.append(t3_3);

    QList<QList<cTrabalho> > nsolucao;
    nsolucao.append(l1);
//    nsolucao.append(l2);
//    nsolucao.append(l3);

    return nsolucao;
}
