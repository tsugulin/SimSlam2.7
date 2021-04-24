#include "Unbatch.h"
Define_Module(Unbatch);

void Unbatch::handleMessage(cMessage *msg)
{
    if (msg->hasObject("msgs")) {
        // ���b�Z�[�W���I�u�W�F�N�g���܂�ł���ꍇ
        cObject *obj = msg->getObject("msgs");  // ���b�Z�[�W�̑҂��s������o��
        cQueue *msgs = check_and_cast<cQueue *>(obj);
        while (!msgs->isEmpty())
            send(check_and_cast<cMessage *>(msgs->pop()), "out");    // �L���[�ɗ��܂��Ă��郁�b�Z�[�W�����H���ɑ��o
    }
    delete msg;
}

//�@����������\��
void Unbatch::finish()
{
    EV << "Batch jobs Count: " << stats.getCount() << endl;
}
