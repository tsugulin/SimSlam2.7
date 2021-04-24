#include "Batch.h"
Define_Module(Batch);

void Batch::initialize()
{
    imax = par("workUnit");         // バッチにて集約する個数
    idx = 0;                        // 連番を初期化
    msgs = new cQueue("msgs");       // オブジェクトを生成
    batch = new cMessage("batch");  // バッチメッセージの作成
}

void Batch::handleMessage(cMessage *msg)
{
    // 前工程から届いたメッセージの場合，アクティビティを開始
    msgs->insert(msg);          // バッチにメッセージを追加
    if (++idx >= imax) {
        // 必要個数溜まった場合
        batch->addObject(msgs);         // メッセージに待ち行列を追加
        send(batch, "out");             // 次工程にバッチメッセージを送信
        idx = 0;                        // 連番を初期化
        msgs = new cQueue("msgs");       // オブジェクトを生成
        batch = new cMessage("batch");  // バッチメッセージの作成
        stats.collect(0);               // 送信個数を記録
    }
}

//　処理件数を表示
void Batch::finish()
{
    EV << "Batch jobs Count: " << stats.getCount() << endl;
    delete msgs;
    delete batch;
}
