#include "Lockup.h"
Define_Module(Lockup);
#include "Resource.h"

void Lockup::initialize()
{
    queue.setName("queue");         // GUIに待ち行列長さを表示するための名前
    qlen.init(simTime(), 100);

    // リソースのポインタを取得
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void Lockup::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // アクティビティ終了時
        stats.collect(simTime() - msg->getTimestamp());  // アクティビティ処理時間をに保管
        send(msg, "out");       // 後工程に送る
    }
    else {
        // 前工程から届いたメッセージの場合
        qlen.set(simTime(), queue.getLength());     // 待ち行列平均長さを計算
        queue.insert(msg);      // 待ち行列の最後尾にめメッセージを追加
    }
    goForward();                // 待ち行列に溜まっているメッセージを処理
}

// 待ち行列にメッセージがあれば処理する
void Lockup::goForward()
{
    Enter_Method("goForward");
    if (queue.getLength() > 0) {
        cMessage *msg = check_and_cast<cMessage *>(queue.front());  // 待ち行列の先頭メッセージを取り出す
        if ( rsc->request(msg->getId()) ) {                         // リソースを要求
            qlen.set(simTime(), queue.getLength());                 // 待ち行列平均長さを計算
            queue.pop();                                            // 待ち行列からメッセージを取り出す
            scheduleAt(simTime() + par("workTime"), msg);           // アクティビティの時間稼ぎ
        }
    }
}

//　ノードの統計情報を表示
void Lockup::finish()
{
    EV << "Await Jobs Count:   " << stats.getCount() << endl;
    EV << "Await AVG Length: " << qlen.get(simTime()) << endl;
}

