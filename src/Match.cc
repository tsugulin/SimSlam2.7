#include "Match.h"
Define_Module(Match);
#include "Array.h"

void Match::initialize()
{
    // �O�H���̃|�C���^���擾
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

// �����Е��̃m�[�h�Ɉ�v����҂��s�񂪂���Ύ��ɑ���
bool Match::check(const char *name, long idx)
{
    Enter_Method("check");
    if (strcmp(name, "Queue4") == 0 && before2->check(idx))
        return  true;
    else if (strcmp(name, "Queue5") == 0 && before1->check(idx))
        return true;
    else
        return false;
}

void Match::finish()
{
    EV << "Match jobs Count: " << stats.getCount() << endl;
}
