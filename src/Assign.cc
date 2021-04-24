#include "Assign.h"
Define_Module(Assign);

void Assign::initialize()
{
    kind = 1;   // �A�Ԃ�������
}

void Assign::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�I����
        if (strcmp(msg->getName(), "patient") == 0) {
            stats1.collect(simTime() - msg->getTimestamp());  // �A�N�e�B�r�e�B�������Ԃ��ɕۊ�
            send(msg, "out1");      // ���҂�ҍ�����
        }
        else {
            stats2.collect(simTime() - msg->getTimestamp());  // �A�N�e�B�r�e�B�������Ԃ��ɕۊ�
            send(msg, "out2");      // �J���e��ۊǎ���
        }
    }
    else {
        // �O�H������͂������b�Z�[�W�̏ꍇ�C�A�N�e�B�r�e�B���J�n
        msg->setKind(kind++);                       // �A�Ԃ��C���N�������g
        msg->setTimestamp(simTime());               // ���[�h�^�C���J�n���Ԃ��Z�b�g
        cMessage *copy = (cMessage *) msg->dup();   // ���b�Z�[�W�̕������쐬
        msg->setName("patient");
        copy->setName("karte");
        if (dblrand(0) < 0.3)
            scheduleAt(simTime() + par("workTime1"), msg);   // 3���͌������󂯂Ă���f�@����
        else
            scheduleAt(simTime() + par("workTime2"), msg);   // 7���͐f�@����
        scheduleAt(simTime() + par("workTime3"), copy);      // �J���e
    }
}

//�@����������\��
void Assign::finish()
{
    EV << "Patient jobs Count:   " << stats1.getCount() << endl;
    EV << "Patient Min WorkTime: " << stats1.getMin() << endl;
    EV << "Patient Avg WorkTime: " << stats1.getMean() << endl;
    EV << "Patient Max WorkTime: " << stats1.getMax() << endl;
    EV << "Patient Standard deviation: " << stats1.getStddev() << endl;
    EV << "Karte jobs Count: "   << stats2.getCount() << endl;
    EV << "Karte Min WorkTime: " << stats2.getMin() << endl;
    EV << "Karte Avg WorkTime: " << stats2.getMean() << endl;
    EV << "Karte Max WorkTime: " << stats2.getMax() << endl;
    EV << "Karte Standard deviation: " << stats2.getStddev() << endl;
}

