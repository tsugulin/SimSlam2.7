#include "Process.h"
Define_Module(Process);
#include "Resource.h"

void Process::initialize()
{
    // リソースのポインタを取得
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void Process::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // アクティビティの終了
        rsc->release( msg->getKind() );                     // リソースの開放
        stats.collect( simTime() - msg->getTimestamp() );   // 処理時間
        delete msg;
    }
    else {
        // 物流のアクティビティの開始
        send(msg, "out");   // バッチメッセージを後工程に送る
        self = new cMessage("release");
        self->setKind(msg->getId());     // バッチメッセージのIDをKindにセット
        self->setTimestamp(simTime());   // リードタイム開始時間をセット
        scheduleAt(simTime() + par("workTime"), self);
    }
}

void Process::finish()
{
    EV << "Process jobs Count: " << stats.getCount() << endl;
}
