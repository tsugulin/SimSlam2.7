#include "Array.h"
Define_Module(Array);
#include "Match.h"

void Array::initialize()
{
    // 変数初期化
    ary.setName("queue");           // GUIに待ち行列長さを表示するための名前
    qName = par("qName");           // 待ち行列の名前
    qlen.init(simTime(), maxQnum);  // 待ち行列の平均長さを計算するクラスを初期化
    length = 0;                     // 待ち行列数を初期化

    // 次工程のマッチノードを取得
    cModule *mod = gate("out")->getNextGate()->getOwnerModule();
    next = check_and_cast<Match *>(mod);
}

void Array::handleMessage(cMessage *msg)
{
    qlen.set(simTime(), length);    // 待ち行列長さの加重平均値の計算
    length++;                       // 要素数を増やす
    msg->setTimestamp(simTime());   // リードタイム開始時間をセット
    ary.addAt(msg->getKind(), msg); // メッセージを配列に保管
    displayArray();                 // 配列の状況を表示
    startActivity(msg->getKind());
}

// 処理待ちがあればアクティビティを開始する
void Array::startActivity(long idx)
{
    Enter_Method("startActivity");
    if (length > 0) {       // 在庫が在れば
        if (next->check(idx)) {
            qlen.set(simTime(), length);                            // 待ち行列長さの加重平均値の計算
            cMessage *msg = check_and_cast<cMessage *>(ary[idx]);   // メッセージ取り出し
            ary.remove(idx);                                        // 配列をアンリンク
            displayArray();                                         //　配列の状況を表示
            length--;                                               // 要素数を減らす
            send(msg, "out");                                       // 次工程に送信
            stats.collect(simTime() - msg->getTimestamp());         // キュー滞留時間を保管
        }
    }
}

// マッチノードから呼び出され，同じ番号の要素が存在すればTrueを返す
bool Array::check(long idx)
{
    Enter_Method("check");
    return ary.exist(idx);
}

// マッチノードから呼び出され，同じ番号の要素が削除する
void Array::remove(long idx)
{
    Enter_Method("remove");
    if (ary.exist(idx)) {
        qlen.set(simTime(), length);    // 待ち行列長さの加重平均値の計算
        length--;                       // 要素数を減らす
        cMessage *msg = check_and_cast<cMessage *>(ary[idx]);   // メッセージ取り出し
        stats.collect(simTime() - msg->getTimestamp());          // キュー滞留時間を保管
        delete ary.remove(idx);         // 配列とメッセージを削除
        displayArray();                 //　配列の状況を表示
    }
}

// シミュレーション実行画面のアイコンに待ち状況を表示する
void Array::displayArray()
{
    std::string str;     // 空の文字列を作成
    for (cArray::Iterator it(ary); !it.end(); it++) {
        cMessage *msg = check_and_cast<cMessage *>(*it);
        str += "," + std::to_string(msg->getKind());    // 患者やカルテの連番を列記
    }
    str.erase(0,1);     // 先頭文字を削除
    getDisplayString().setTagArg("t", 0, str.c_str());  // シミュレーション画面に表示
}

//　ノードの統計情報を表示
void Array::finish()
{
    EV << qName << " AVG Length:   " << qlen.get(simTime()) << endl;
    EV << qName << " Jobs Count:   " << stats.getCount() << endl;
    EV << qName << " Min WaitTime: " << stats.getMin() << endl;
    EV << qName << " Avg WaitTime: " << stats.getMean() << endl;
    EV << qName << " Max WaitTime: " << stats.getMax() << endl;
    EV << qName << " Standard deviation: " << stats.getStddev() << endl;
}
