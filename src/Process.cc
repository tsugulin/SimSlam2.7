#include "Process.h"
Define_Module(Process);
#include "Resource.h"

void Process::initialize()
{
    // ���\�[�X�̃|�C���^���擾
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void Process::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�̏I��
        rsc->release( msg->getKind() );                     // ���\�[�X�̊J��
        stats.collect( simTime() - msg->getTimestamp() );   // ��������
        delete msg;
    }
    else {
        // �����̃A�N�e�B�r�e�B�̊J�n
        send(msg, "out");   // �o�b�`���b�Z�[�W����H���ɑ���
        self = new cMessage("release");
        self->setKind(msg->getId());     // �o�b�`���b�Z�[�W��ID��Kind�ɃZ�b�g
        self->setTimestamp(simTime());   // ���[�h�^�C���J�n���Ԃ��Z�b�g
        scheduleAt(simTime() + par("workTime"), self);
    }
}

void Process::finish()
{
    EV << "Process jobs Count: " << stats.getCount() << endl;
}
