#include "BlockingQueue.h"
Define_Module(BlockingQueue);

void BlockingQueue::initialize()
{
    // 変数初期化
    onActivity = false;             // 現在は生産中ではない
    queue.setName("queue");         // GUIに待ち行列長さを表示するための名前
    qName = par("qName");           // 待ち行列の名前
    qlen.init(simTime(), maxQnum);  // 待ち行列の平均長さを計算するクラスを初期化
}

void BlockingQueue::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // アクティビティ終了時
        send(msg, "out");       // 後工程に送る
        onActivity = false;   // アクティビティ終了とする
    }
    else {
        // 前工程から届いたメッセージの場合
        qlen.set(simTime(), queue.getLength()); // 待ち行列長さの加重平均値の計算
        msg->setTimestamp(simTime());           // リードタイム開始時間をセット
        queue.insert(msg);                      // 待ち行列の最後尾にメッセージを保管
    }
    // 生産を行う
    startActivity();
}

// 処理待ちがあればアクティビティを開始する
void BlockingQueue::startActivity(void)
{
    Enter_Method("startActivity");
    if (queue.getLength() > 0) {    // 在庫が在れば
        if (!onActivity) {                // 生産中で無ければ
            // アクティビティを開始
            qlen.set(simTime(), queue.getLength());                 // 待ち行列長さの加重平均値の計算
            cMessage *msg = check_and_cast<cMessage *>(queue.pop());    // 待ち行列先頭のメッセージを取り出す
            stats.collect(simTime() - msg->getTimestamp());          // キュー滞留時間を保管
            onActivity = true;                                      // フラグをON
            scheduleAt(simTime() + par("workTime"), msg);           // アクティビティ終了後に自身にメッセージを送る
        }
    }
}

//　ノードの統計情報を表示
void BlockingQueue::finish()
{
    EV << qName << " AVG Length:   " << qlen.get(simTime()) << endl;
    EV << qName << " Jobs Count:   " << stats.getCount() << endl;
    EV << qName << " Min WaitTime: " << stats.getMin() << endl;
    EV << qName << " Avg WaitTime: " << stats.getMean() << endl;
    EV << qName << " Max WaitTime: " << stats.getMax() << endl;
    EV << qName << " Standard deviation: " << stats.getStddev() << endl;
}
