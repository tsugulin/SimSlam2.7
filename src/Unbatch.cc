#include "Unbatch.h"
Define_Module(Unbatch);

void Unbatch::handleMessage(cMessage *msg)
{
    if (msg->hasObject("msgs")) {
        // メッセージがオブジェクトを含んでいる場合
        cObject *obj = msg->getObject("msgs");  // メッセージの待ち行列を取り出し
        cQueue *msgs = check_and_cast<cQueue *>(obj);
        while (!msgs->isEmpty())
            send(check_and_cast<cMessage *>(msgs->pop()), "out");    // キューに溜まっているメッセージを次工程に送出
    }
    delete msg;
}

//　処理件数を表示
void Unbatch::finish()
{
    EV << "Batch jobs Count: " << stats.getCount() << endl;
}
