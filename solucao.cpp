#include "solucao.h"

#define MAX(a,b) (((a)<(b))?(b):(a))

Solucao::Solucao(){
    QList<QList<cTrabalho> > t;
    trabalhos = t;

    QString l("");
    nome_maquinas.append(l);

    escala = 90;
}

Solucao Solucao::GerarSolucao2(){
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    int alpha = 255;
//    QColor cor_trabalho = QColor(qrand()%255,qrand()%255,qrand()%255,alpha);
//    cTrabalho m1_d1(QTime(1,20),QTime(2,10),QDate::currentDate(),QDate::currentDate(),"m1_d1",cor_trabalho);
//    cTrabalho m1_d2(QTime(2,0),QTime(3,25),QDate::currentDate().addDays(1),QDate::currentDate().addDays(1),"m1_d2",cor_trabalho);
//
//    cTrabalho m2_d1(QTime(1,20),QTime(2,10),QDate::currentDate(),QDate::currentDate(),"m2_d1",cor_trabalho);
//    cTrabalho m2_d2(QTime(2,0),QTime(3,25),QDate::currentDate().addDays(1),QDate::currentDate().addDays(1),"m2_d2",cor_trabalho);
//
//    /*maquina1*/
//    dataCelula dc1;
//    QList<cTrabalho> lt1;
//    lt1.append(m1_d1);
//    dc1.trabalhos = lt1;
//    dc1.data = QDate::currentDate();
//
//    celulaTrabalho ct1;
//    ct1.nome = "maquina 1";
//    ct1.dia = dc1;
//
//
//    /*maquina2*/
//    dataCelula dc2;
//    QList<cTrabalho> lt2;
//    lt2.append(m1_d2);
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
    nome_maquinas.append("Máquina de corte");
    nome_maquinas.append("Máquina de pintura");
    nome_maquinas.append("Máquina de acabamento");
    nome_maquinas.append("Máquina de polimento");

    //qDebug() << "lolwut " << nome_maquinas.size();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int alpha = 255;
    QColor cor_trabalho = QColor(qrand()%255,qrand()%255,qrand()%255,alpha);

    cTrabalho t1_1(QTime(8,15), QTime(8,42),QDate::currentDate(),QDate::currentDate(),"t1_1",cor_trabalho);
    cTrabalho t1_2(QTime(9,0), QTime(9,50),QDate::currentDate(),QDate::currentDate(),"t1_2",cor_trabalho);
    cTrabalho t1_3(QTime(10,0), QTime(11,25),QDate::currentDate(),QDate::currentDate(),"t1_3",cor_trabalho);
    cTrabalho t1_4(QTime(13,0), QTime(15,0),QDate::currentDate(),QDate::currentDate(),"t1_4",cor_trabalho);
    cTrabalho t1_5(QTime(15,20), QTime(17,55),QDate::currentDate(),QDate::currentDate(),"t1_5",cor_trabalho);
//
    cTrabalho t2_0(QTime(6,0), QTime(8,20),QDate::currentDate(),QDate::currentDate(),"t2_0",cor_trabalho);
    cTrabalho t2_1(QTime(8,30), QTime(9,20),QDate::currentDate(),QDate::currentDate(),"t2_1",cor_trabalho);
    cTrabalho t2_2(QTime(10,0), QTime(12,0),QDate::currentDate(),QDate::currentDate(),"t2_2",cor_trabalho);
    cTrabalho t2_3(QTime(13,20), QTime(14,0),QDate::currentDate(),QDate::currentDate(),"t2_3",cor_trabalho);
    cTrabalho t2_4(QTime(14,7), QTime(18,0),QDate::currentDate(),QDate::currentDate(),"t2_3",cor_trabalho);

    cTrabalho tempo_setup(QTime(7,0),QTime(8,30),QDate::currentDate(),QDate::currentDate(),"tempo_setup",QColor(0,0,0,255), true);
    cTrabalho t3_1(QTime(8,30), QTime(9,0),QDate::currentDate(),QDate::currentDate(),"t3_1",cor_trabalho);
    cTrabalho t3_2(QTime(9,10), QTime(9,20),QDate::currentDate(),QDate::currentDate(),"t3_2",cor_trabalho);
    cTrabalho t3_3(QTime(9,55), QTime(10,20),QDate::currentDate(),QDate::currentDate(),"t3_3",cor_trabalho);
    cTrabalho t3_4(QTime(11,0), QTime(13,0),QDate::currentDate().addDays(2),QDate::currentDate().addDays(2),"t3_4",cor_trabalho);

    cTrabalho t4_1(QTime(12,0), QTime(12,50),QDate::currentDate().addDays(2),QDate::currentDate().addDays(2),"t4_1",cor_trabalho);
    QList<cTrabalho> l4;
    l4.append(t4_1);
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

//    QList<QString> nome_maquinas;
//    QList<QList<cTrabalho> > nsolucao;
//    for(int x=0 ; x<10 ; x++){
//        QList<cTrabalho> l1;
//        for(int y=0; y<24 ; y++){
//            cTrabalho t1_1(QTime(y,0),QTime(y+1,0),QDate::currentDate(),QDate::currentDate(),"t1_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//            l1.append(t1_1);
//        }
//        nome_maquinas.append("m1");
//        nsolucao.append(l1);
//    }

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
    l3.append(tempo_setup);
    l3.append(t3_1);
    l3.append(t3_2);
    l3.append(t3_3);
    l3.append(t3_4);

    QList<QList<cTrabalho> > nsolucao;
    nsolucao.append(l1);
    nsolucao.append(l2);
    nsolucao.append(l3);
    nsolucao.append(l4);
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

QDate Solucao::getDataInicio(){
    QList<QDate> lista_data;
    QDate menor_data;
    foreach(QList<cTrabalho> maquina, trabalhos){
        menor_data = maquina.first().getDataInicio();
        foreach(cTrabalho trabalho, maquina){
            if(menor_data>trabalho.getDataInicio()){
                menor_data = trabalho.getDataInicio();
            }
        }
        lista_data.append(menor_data);
    }
    menor_data = lista_data.first();
    foreach(QDate data, lista_data){
        if(menor_data>data){
            menor_data = data;
        }
    }
    return menor_data;
}

int Solucao::getDiasTrabalho(cTrabalho trabalho){
    return this->getDataInicio().daysTo(trabalho.getInicio().date());
}

float Solucao::getCoordTrabalho(cTrabalho trabalho){
    //int dias = solucao_inicio.daysTo(t_inicio.date());
    int dias = this->getDataInicio().daysTo(trabalho.getInicio().date());
    float h = trabalho.getInicio().time().hour();
    float m = trabalho.getInicio().time().minute();
    //return (24*dias)+(h+(m/60));
    return (h+(m/60));
}

QDate Solucao::getDataFinal(){
    QList<QDate> lista_data;
    QDate maior_data;
    foreach(QList<cTrabalho> maquina, trabalhos){
        maior_data = maquina.last().getDataFim();
        foreach(cTrabalho trabalho, maquina){
            if(maior_data<trabalho.getDataFim()){
                maior_data = trabalho.getDataFim();
            }
        }
        lista_data.append(maior_data);
    }
    maior_data = lista_data.first();
    foreach(QDate data, lista_data){
        if(maior_data<data){
            maior_data = data;
        }
    }
    return maior_data;
}

int Solucao::getMaiorNomeMaquina(){
    int maior = 0;
    QFont myFont;
    QFontMetrics fmetrics(myFont);
    foreach(QString nome, nome_maquinas){
        maior = MAX(maior,fmetrics.boundingRect(nome).width());
    }
    //+15 gambiarra pra ficar do tamanho certo
    return maior+15;
}

void Solucao::debugarSolucao(){
    foreach(QList<cTrabalho> maquina, trabalhos){
        foreach(cTrabalho trab, maquina){
            qDebug() << trab.getTexto();
        }
    }
}
