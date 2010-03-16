#include "scheduling.h"

#define MAX(a,b) (((a)<(b))?(b):(a))

Scheduling::Scheduling(){
    QList<QList<Task> > t;
    tasks = t;

    QString l("");
    nome_celulas_trabalho.append(l);

    escala = 90;
}

//Scheduling Scheduling::GerarScheduling2(){
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    int alpha = 255;
//    QColor cor_task = QColor(qrand()%255,qrand()%255,qrand()%255,alpha);
//    Task m1_d1(QTime(1,20),QTime(2,10),QDate::currentDate(),QDate::currentDate(),"m1_d1",cor_task);
//    Task m1_d2(QTime(2,0),QTime(3,25),QDate::currentDate().addDays(1),QDate::currentDate().addDays(1),"m1_d2",cor_task);
//
//    Task m2_d1(QTime(1,20),QTime(2,10),QDate::currentDate(),QDate::currentDate(),"m2_d1",cor_task);
//    Task m2_d2(QTime(2,0),QTime(3,25),QDate::currentDate().addDays(1),QDate::currentDate().addDays(1),"m2_d2",cor_task);
//
//    /*maquina1*/
//    dataCelula dc1;
//    QList<Task> lt1;
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
//    QList<Task> lt2;
//    lt2.append(m1_d2);
//}

Scheduling Scheduling::SchedulingVazia(){
    Task t(QTime(0,0),QTime(0,0),QDate(1500,1,1),QDate(1500,1,1),"",QColor(0,0,0,0));
    QList<Task> l;
    l.append(t);
    QList<QList<Task> > s;
    s.append(l);
    Scheduling sol;
    sol.setTasks(s);
    QList<QString> nome_celulas_trabalho;
    nome_celulas_trabalho.append("maquina 1");
    sol.setNomeCelulasTrabalho(nome_celulas_trabalho);
    return sol;
}

Scheduling Scheduling::GerarScheduling(){

    QList<QString> nome_celulas_trabalho;
    nome_celulas_trabalho.append("Máquina de corte");
    nome_celulas_trabalho.append("Máquina de pintura");
    nome_celulas_trabalho.append("Máquina de acabamento");
    nome_celulas_trabalho.append("Máquina de polimento");

    //qDebug() << "lolwut " << nome_celulas_trabalho.size();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int alpha = 255;
    QColor cor_task = QColor(qrand()%255,qrand()%255,qrand()%255,alpha);

    Task t1_1(QTime(8,15), QTime(8,42),QDate::currentDate(),QDate::currentDate(),"t1_1",cor_task);
    Task t1_2(QTime(9,0), QTime(9,50),QDate::currentDate(),QDate::currentDate(),"t1_2",cor_task);
    Task t1_3(QTime(10,0), QTime(11,25),QDate::currentDate(),QDate::currentDate(),"t1_3",cor_task);
    Task t1_4(QTime(13,0), QTime(15,0),QDate::currentDate(),QDate::currentDate(),"t1_4",cor_task);
    Task t1_5(QTime(15,20), QTime(17,55),QDate::currentDate(),QDate::currentDate(),"t1_5",cor_task);
//
    Task t2_0(QTime(6,0), QTime(8,20),QDate::currentDate(),QDate::currentDate(),"t2_0",cor_task);
    Task t2_1(QTime(8,30), QTime(9,20),QDate::currentDate(),QDate::currentDate(),"t2_1",cor_task);
    Task t2_2(QTime(10,0), QTime(12,0),QDate::currentDate(),QDate::currentDate(),"t2_2",cor_task);
    Task t2_3(QTime(13,20), QTime(14,0),QDate::currentDate(),QDate::currentDate(),"t2_3",cor_task);
    Task t2_4(QTime(14,7), QTime(18,0),QDate::currentDate(),QDate::currentDate(),"t2_3",cor_task);

    Task tempo_setup(QTime(7,0),QTime(8,30),QDate::currentDate(),QDate::currentDate(),"tempo_setup",QColor(0,0,0,255), true);
    Task t3_1(QTime(8,30), QTime(9,0),QDate::currentDate(),QDate::currentDate(),"t3_1",cor_task);
    Task t3_2(QTime(9,10), QTime(9,20),QDate::currentDate(),QDate::currentDate(),"t3_2",cor_task);
    Task t3_3(QTime(9,55), QTime(10,20),QDate::currentDate(),QDate::currentDate(),"t3_3",cor_task);
    Task t3_4(QTime(11,0), QTime(13,0),QDate::currentDate().addDays(2),QDate::currentDate().addDays(2),"t3_4",cor_task);

    Task t4_1(QTime(12,0), QTime(12,50),QDate::currentDate().addDays(2),QDate::currentDate().addDays(2),"t4_1",cor_task);
    QList<Task> l4;
    l4.append(t4_1);
//
//    Task t5_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l5;
//    l5.append(t5_1);
//
//    Task t6_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l6;
//    l6.append(t6_1);
//
//    Task t7_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l7;
//    l7.append(t7_1);
//
//    Task t8_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l8;
//    l8.append(t8_1);
//
//    Task t9_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l9;
//    l9.append(t9_1);
//
//    Task t10_1(QTime(3,0), QTime(4,0), "t3_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//    QList<Task> l10;
//    l10.append(t10_1);

//    QList<QString> nome_celulas_trabalho;
//    QList<QList<Task> > nscheduling;
//    for(int x=0 ; x<10 ; x++){
//        QList<Task> l1;
//        for(int y=0; y<24 ; y++){
//            Task t1_1(QTime(y,0),QTime(y+1,0),QDate::currentDate(),QDate::currentDate(),"t1_1",QColor(qrand()%255,qrand()%255,qrand()%255,alpha));
//            l1.append(t1_1);
//        }
//        nome_celulas_trabalho.append("m1");
//        nscheduling.append(l1);
//    }

    QList<Task> l1;
    l1.append(t1_1);
    l1.append(t1_2);
    l1.append(t1_3);
    l1.append(t1_4);
    l1.append(t1_5);

    QList<Task> l2;
    l2.append(t2_0);
    l2.append(t2_1);
    l2.append(t2_2);
    l2.append(t2_3);
    l2.append(t2_4);

    QList<Task> l3;
    l3.append(tempo_setup);
    l3.append(t3_1);
    l3.append(t3_2);
    l3.append(t3_3);
    l3.append(t3_4);

    QList<QList<Task> > nscheduling;
    nscheduling.append(l1);
    nscheduling.append(l2);
    nscheduling.append(l3);
    nscheduling.append(l4);
//    nscheduling.append(l5);
//    nscheduling.append(l6);
//    nscheduling.append(l7);
//    nscheduling.append(l8);
//    nscheduling.append(l9);
//    nscheduling.append(l10);

    Scheduling scheduling;
    scheduling.setTasks(nscheduling);
    scheduling.setNomeCelulasTrabalho(nome_celulas_trabalho);

    return scheduling;
}

int Scheduling::getDiasDuracao(){
    int maior = 0;
    foreach(QList<Task> celula_trabalho, tasks){
        maior = MAX(celula_trabalho.first().getDataInicio().daysTo(celula_trabalho.last().getDataFim()),maior);
    }
    return maior;
}

QDate Scheduling::getDataInicio(){
    QList<QDate> lista_data;
    QDate menor_data;
    foreach(QList<Task> celula_trabalho, tasks){
        menor_data = celula_trabalho.first().getDataInicio();
        foreach(Task task, celula_trabalho){
            if(menor_data>task.getDataInicio()){
                menor_data = task.getDataInicio();
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

int Scheduling::getDiasTask(Task task){
    return this->getDataInicio().daysTo(task.getInicio().date());
}

float Scheduling::getCoordTask(Task task){
    //int dias = scheduling_inicio.daysTo(t_inicio.date());
    //int dias = this->getDataInicio().daysTo(trabalho.getInicio().date());
    float h = task.getInicio().time().hour();
    float m = task.getInicio().time().minute();
    //return (24*dias)+(h+(m/60));
    return (h+(m/60));
}

QDate Scheduling::getDataFinal(){
    QList<QDate> lista_data;
    QDate maior_data;
    foreach(QList<Task> celula_trabalho, tasks){
        maior_data = celula_trabalho.last().getDataFim();
        foreach(Task task, celula_trabalho){
            if(maior_data<task.getDataFim()){
                maior_data = task.getDataFim();
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

int Scheduling::getMaiorNomeCelulaTrabalho(){
    int maior = 0;
    QFont myFont;
    QFontMetrics fmetrics(myFont);
    foreach(QString nome, nome_celulas_trabalho){
        maior = MAX(maior,fmetrics.boundingRect(nome).width());
    }
    //+15 gambiarra pra ficar do tamanho certo
    return maior+15;
}

void Scheduling::debugarScheduling(){
    foreach(QList<Task> celula_trabalho, tasks){
        foreach(Task task, celula_trabalho){
            qDebug() << task.getTexto();
        }
    }
}
