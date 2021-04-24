#include "Match.h"
Define_Module(Match);
#include "Array.h"

void Match::initialize()
{
    // 前工程のポインタを取得
    mod1 = gate("in1")->getPreviousGate()->getOwnerModule();
    mod2 = gate("in2")->getPreviousGate()->getOwnerModule();
    before1 = check_and_cast<Array *>(mod1);
    before2 = check_and_cast<Array *>(mod2);
}

void Match::handleMessage(cMessage *msg)
{
    if (msg->getSenderModule() == mod1)
        before2->remove(msg->getKind());
    else
        before1->remove(msg->getKind());
    send(msg, "out");
}

// もう片方のノードに一致する待ち行列があれば次に送る
bool Match::check(long idx)
{
    Enter_Method("check");
    return (before1->check(idx) && before2->check(idx)) ? true: false;
}

void Match::finish()
{
    EV << "Match jobs Count: " << stats.getCount() << endl;
}
