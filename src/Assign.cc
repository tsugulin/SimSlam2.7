#include "Assign.h"
Define_Module(Assign);

void Assign::initialize()
{
    kind = 1;   // 連番を初期化
}

void Assign::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // アクティビティ終了時
        if (strcmp(msg->getName(), "patient") == 0) {
            stats1.collect(simTime() - msg->getTimestamp());  // アクティビティ処理時間をに保管
            send(msg, "out1");      // 患者を待合室へ
        }
        else {
            stats2.collect(simTime() - msg->getTimestamp());  // アクティビティ処理時間をに保管
            send(msg, "out2");      // カルテを保管室へ
        }
    }
    else {
        // 前工程から届いたメッセージの場合，アクティビティを開始
        msg->setKind(kind++);                       // 連番をインクリメント
        msg->setTimestamp(simTime());               // リードタイム開始時間をセット
        cMessage *copy = (cMessage *) msg->dup();   // メッセージの複製を作成
        msg->setName("patient");
        copy->setName("karte");
        if (dblrand(0) < 0.3)
            scheduleAt(simTime() + par("workTime1"), msg);   // 3割は検査を受けてから診察室へ
        else
            scheduleAt(simTime() + par("workTime2"), msg);   // 7割は診察室へ
        scheduleAt(simTime() + par("workTime3"), copy);      // カルテ
    }
}

//　処理件数を表示
void Assign::finish()
{
    EV << "Patient jobs Count:   " << stats1.getCount() << endl;
    EV << "Patient Min WorkTime: " << stats1.getMin() << endl;
    EV << "Patient Avg WorkTime: " << stats1.getMean() << endl;
    EV << "Patient Max WorkTime: " << stats1.getMax() << endl;
    EV << "Patient Standard deviation: " << stats1.getStddev() << endl;
    EV << "Karte jobs Count: "   << stats2.getCount() << endl;
    EV << "Karte Min WorkTime: " << stats2.getMin() << endl;
    EV << "Karte Avg WorkTime: " << stats2.getMean() << endl;
    EV << "Karte Max WorkTime: " << stats2.getMax() << endl;
    EV << "Karte Standard deviation: " << stats2.getStddev() << endl;
}

