// メッセージを指定個数，指定間隔にて生成する

#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    beatMsg = new cMessage("beat"); // 繰り返し生成するメッセージを１つだけ生成
    scheduleAt(simTime(), beatMsg); // 最初のメッセージを自身に送信
}

void Create::handleMessage(cMessage *msg)
{
    // 次のモジュールにメッセージを送信
    send(new cMessage("data"), "out");

    //　intervalTimeのピッチにてheartbeatメッセージを自身に送信する
    double d = par("intervalTime");
    scheduleAt(simTime() + d, msg);
}
