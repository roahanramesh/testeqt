#include "solucao.h"

#define MAX(a,b) (((a)<(b))?(b):(a))

Solucao::Solucao(){
    makespan = 1561;
    maior_atraso = 24875;
    num_op_atrasadas = 456515;
    total_atrasos = 12315;
    custo_mao_de_obra = 1515;
    custos_operacionais = 11541;
    total_setup = 65165;
    total_ociosidade = 651814;
    total_folga = 78944;

    QList<QList<cTrabalho> > t;
    trabalhos = t;

    QString l("");
    nome_maquinas.append(l);

    escala = 120;
}

Solucao Solucao::SolucaoVazia(){
    cTrabalho t(QTime(0,0),QTime(0,0),QDate(1500,1,1),QDate(1500,1,1),"",QColor(0,0,0,0));
    QList<cTrabalho> l;
    l.append(t);
    QList<QList<cTrabalho> > s;
    s.append(l);
    Solucao sol;
    sol.setTrabalhos(s);
    QList<QString> nome_maquinas;
    nome_maquinas.append("maquina 1");
    sol.setNomeMaquinas(nome_maquinas);
    return sol;
}

Solucao Solucao::GerarSolucao(){

    QList<QString> nome_maquinas;
    nome_maquinas.append("M�quina de corte");
    nome_maquinas.append("M�quina de pintura");
    nome_maquinas.append("M�quina de acabamento");

    //qDebug() << "lolwut " << nome_maquinas.size();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int alpha = 255;
    cTrabalho t1_1(QTime(0,15),QTime(1,30),QDate::currentDate(),QDate::currentDate(),"t1_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t1_2(QTime(2,25),QTime(3,48),QDate::currentDate(),QDate::currentDate(),"t1_2",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t1_3(QTime(6,0),QTime(7,0),QDate::currentDate(),QDate::currentDate(),"t1_3",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t1_4(QTime(8,0),QTime(10,0),QDate::currentDate(),QDate::currentDate(),"t1_4",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t1_5(QTime(15,0),QTime(18,0),QDate::currentDate(),QDate::currentDate().addDays(40),"t1_5",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));

    cTrabalho t2_0(QTime(0,10), QTime(3,20),QDate::currentDate(),QDate::currentDate(),"t2_0",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t2_1(QTime(6,0), QTime(12,0),QDate::currentDate(),QDate::currentDate(),"t2_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t2_2(QTime(12,0), QTime(15,0),QDate::currentDate(),QDate::currentDate(),"t2_2",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t2_3(QTime(15,0), QTime(18,0),QDate::currentDate(),QDate::currentDate(),"t2_3",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t2_4(QTime(19,0), QTime(22,0),QDate::currentDate(),QDate::currentDate(),"t2_3",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));

    cTrabalho overhead(QTime(0,0),QTime(1,0),QDate::currentDate(),QDate::currentDate(),"Overhead",QColor(0,0,0,255), true);
    cTrabalho t3_1(QTime(1,0), QTime(2,0),QDate::currentDate(),QDate::currentDate(),"t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t3_2(QTime(2,0), QTime(3,0),QDate::currentDate(),QDate::currentDate(),"t3_2",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
    cTrabalho t3_3(QTime(8,0), QTime(10,0),QDate::currentDate(),QDate::currentDate(),"t3_3",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));

//    cTrabalho t4_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l4;
//    l4.append(t4_1);
//
//    cTrabalho t5_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l5;
//    l5.append(t5_1);
//
//    cTrabalho t6_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l6;
//    l6.append(t6_1);
//
//    cTrabalho t7_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l7;
//    l7.append(t7_1);
//
//    cTrabalho t8_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l8;
//    l8.append(t8_1);
//
//    cTrabalho t9_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l9;
//    l9.append(t9_1);
//
//    cTrabalho t10_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<cTrabalho> l10;
//    l10.append(t10_1);

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
    l3.append(overhead);
    l3.append(t3_1);
    l3.append(t3_2);
    l3.append(t3_3);

    QList<QList<cTrabalho> > nsolucao;
    nsolucao.append(l1);
    nsolucao.append(l2);
    nsolucao.append(l3);
//    nsolucao.append(l4);
//    nsolucao.append(l5);
//    nsolucao.append(l6);
//    nsolucao.append(l7);
//    nsolucao.append(l8);
//    nsolucao.append(l9);
//    nsolucao.append(l10);

    Solucao solucao;
    solucao.setTrabalhos(nsolucao);
    solucao.setNomeMaquinas(nome_maquinas);

    return solucao;
}

int Solucao::getDiasDuracao(){
    int maior = 0;
    foreach(QList<cTrabalho> maquina, trabalhos){
        maior = MAX(maquina.first().getDataInicio().daysTo(maquina.last().getDataFim()),maior);
    }
    return maior;
}

int Solucao::getMaiorNomeMaquina(){
    int maior = 0;
    QFont myFont;
    QFontMetrics fmetrics(myFont);
    foreach(QString nome, nome_maquinas){
        maior = MAX(maior,fmetrics.boundingRect(nome).width());
    }
    //qDebug() << "debug "<< maior;
    //+15 gambiarra pra ficar do tamanho certo
    return maior+15;
}
