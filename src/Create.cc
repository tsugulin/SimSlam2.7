// ���b�Z�[�W���w����C�w��Ԋu�ɂĐ�������

#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    beatMsg = new cMessage("beat"); // �J��Ԃ��������郁�b�Z�[�W���P��������
    scheduleAt(simTime(), beatMsg); // �ŏ��̃��b�Z�[�W�����g�ɑ��M
}

void Create::handleMessage(cMessage *msg)
{
    // ���̃��W���[���Ƀ��b�Z�[�W�𑗐M
    send(new cMessage("data"), "out");

    //�@intervalTime�̃s�b�`�ɂ�heartbeat���b�Z�[�W�����g�ɑ��M����
    double d = par("intervalTime");
    scheduleAt(simTime() + d, msg);
}
