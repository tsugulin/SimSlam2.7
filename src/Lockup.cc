#include "Lockup.h"
Define_Module(Lockup);
#include "Resource.h"

void Lockup::initialize()
{
    queue.setName("queue");         // GUI�ɑ҂��s�񒷂���\�����邽�߂̖��O
    qlen.init(simTime(), 100);

    // ���\�[�X�̃|�C���^���擾
    cModule *mod = gate("res")->getNextGate()->getOwnerModule();
    rsc = check_and_cast<Resource *>(mod);
}

void Lockup::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�I����
        stats.collect(simTime() - msg->getTimestamp());  // �A�N�e�B�r�e�B�������Ԃ��ɕۊ�
        send(msg, "out");       // ��H���ɑ���
    }
    else {
        // �O�H������͂������b�Z�[�W�̏ꍇ
        qlen.set(simTime(), queue.getLength());     // �҂��s�񕽋ϒ������v�Z
        queue.insert(msg);      // �҂��s��̍Ō���ɂ߃��b�Z�[�W��ǉ�
    }
    goForward();                // �҂��s��ɗ��܂��Ă��郁�b�Z�[�W������
}

// �҂��s��Ƀ��b�Z�[�W������Ώ�������
void Lockup::goForward()
{
    Enter_Method("goForward");
    if (queue.getLength() > 0) {
        cMessage *msg = check_and_cast<cMessage *>(queue.front());  // �҂��s��̐擪���b�Z�[�W�����o��
        if ( rsc->request(msg->getId()) ) {                         // ���\�[�X��v��
            qlen.set(simTime(), queue.getLength());                 // �҂��s�񕽋ϒ������v�Z
            queue.pop();                                            // �҂��s�񂩂烁�b�Z�[�W�����o��
            scheduleAt(simTime() + par("workTime"), msg);           // �A�N�e�B�r�e�B�̎��ԉ҂�
        }
    }
}

//�@�m�[�h�̓��v����\��
void Lockup::finish()
{
    EV << "Await Jobs Count:   " << stats.getCount() << endl;
    EV << "Await AVG Length: " << qlen.get(simTime()) << endl;
}

