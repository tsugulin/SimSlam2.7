#include "BlockingQueue.h"
Define_Module(BlockingQueue);

void BlockingQueue::initialize()
{
    // �ϐ�������
    onActivity = false;             // ���݂͐��Y���ł͂Ȃ�
    queue.setName("queue");         // GUI�ɑ҂��s�񒷂���\�����邽�߂̖��O
    qName = par("qName");           // �҂��s��̖��O
    qlen.init(simTime(), maxQnum);  // �҂��s��̕��ϒ������v�Z����N���X��������
}

void BlockingQueue::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�I����
        send(msg, "out");       // ��H���ɑ���
        onActivity = false;   // �A�N�e�B�r�e�B�I���Ƃ���
    }
    else {
        // �O�H������͂������b�Z�[�W�̏ꍇ
        qlen.set(simTime(), queue.getLength()); // �҂��s�񒷂��̉��d���ϒl�̌v�Z
        msg->setTimestamp(simTime());           // ���[�h�^�C���J�n���Ԃ��Z�b�g
        queue.insert(msg);                      // �҂��s��̍Ō���Ƀ��b�Z�[�W��ۊ�
    }
    // ���Y���s��
    startActivity();
}

// �����҂�������΃A�N�e�B�r�e�B���J�n����
void BlockingQueue::startActivity(void)
{
    Enter_Method("startActivity");
    if (queue.getLength() > 0) {    // �݌ɂ��݂��
        if (!onActivity) {                // ���Y���Ŗ������
            // �A�N�e�B�r�e�B���J�n
            qlen.set(simTime(), queue.getLength());                 // �҂��s�񒷂��̉��d���ϒl�̌v�Z
            cMessage *msg = check_and_cast<cMessage *>(queue.pop());    // �҂��s��擪�̃��b�Z�[�W�����o��
            stats.collect(simTime() - msg->getTimestamp());          // �L���[�ؗ����Ԃ�ۊ�
            onActivity = true;                                      // �t���O��ON
            scheduleAt(simTime() + par("workTime"), msg);           // �A�N�e�B�r�e�B�I����Ɏ��g�Ƀ��b�Z�[�W�𑗂�
        }
    }
}

//�@�m�[�h�̓��v����\��
void BlockingQueue::finish()
{
    EV << qName << " AVG Length:   " << qlen.get(simTime()) << endl;
    EV << qName << " Jobs Count:   " << stats.getCount() << endl;
    EV << qName << " Min WaitTime: " << stats.getMin() << endl;
    EV << qName << " Avg WaitTime: " << stats.getMean() << endl;
    EV << qName << " Max WaitTime: " << stats.getMax() << endl;
    EV << qName << " Standard deviation: " << stats.getStddev() << endl;
}
