#include "Array.h"
Define_Module(Array);
#include "Match.h"

void Array::initialize()
{
    // �ϐ�������
    ary.setName("queue");           // GUI�ɑ҂��s�񒷂���\�����邽�߂̖��O
    qName = par("qName");           // �҂��s��̖��O
    qlen.init(simTime(), maxQnum);  // �҂��s��̕��ϒ������v�Z����N���X��������
    length = 0;                     // �҂��s�񐔂�������

    // ���H���̃}�b�`�m�[�h���擾
    cModule *mod = gate("out")->getNextGate()->getOwnerModule();
    next = check_and_cast<Match *>(mod);
}

void Array::handleMessage(cMessage *msg)
{
    qlen.set(simTime(), length);    // �҂��s�񒷂��̉��d���ϒl�̌v�Z
    length++;                       // �v�f���𑝂₷
    msg->setTimestamp(simTime());   // ���[�h�^�C���J�n���Ԃ��Z�b�g
    ary.addAt(msg->getKind(), msg); // ���b�Z�[�W��z��ɕۊ�
    displayArray();                 // �z��̏󋵂�\��
    startActivity(msg->getKind());
}

// �����҂�������΃A�N�e�B�r�e�B���J�n����
void Array::startActivity(long idx)
{
    Enter_Method("startActivity");
    if (length > 0) {       // �݌ɂ��݂��
        if (next->check(idx)) {
            qlen.set(simTime(), length);                            // �҂��s�񒷂��̉��d���ϒl�̌v�Z
            cMessage *msg = check_and_cast<cMessage *>(ary[idx]);   // ���b�Z�[�W���o��
            ary.remove(idx);                                        // �z����A�������N
            displayArray();                                         //�@�z��̏󋵂�\��
            length--;                                               // �v�f�������炷
            send(msg, "out");                                       // ���H���ɑ��M
            stats.collect(simTime() - msg->getTimestamp());         // �L���[�ؗ����Ԃ�ۊ�
        }
    }
}

// �}�b�`�m�[�h����Ăяo����C�����ԍ��̗v�f�����݂����True��Ԃ�
bool Array::check(long idx)
{
    Enter_Method("check");
    return ary.exist(idx);
}

// �}�b�`�m�[�h����Ăяo����C�����ԍ��̗v�f���폜����
void Array::remove(long idx)
{
    Enter_Method("remove");
    if (ary.exist(idx)) {
        qlen.set(simTime(), length);    // �҂��s�񒷂��̉��d���ϒl�̌v�Z
        length--;                       // �v�f�������炷
        cMessage *msg = check_and_cast<cMessage *>(ary[idx]);   // ���b�Z�[�W���o��
        stats.collect(simTime() - msg->getTimestamp());          // �L���[�ؗ����Ԃ�ۊ�
        delete ary.remove(idx);         // �z��ƃ��b�Z�[�W���폜
        displayArray();                 //�@�z��̏󋵂�\��
    }
}

// �V�~�����[�V�������s��ʂ̃A�C�R���ɑ҂��󋵂�\������
void Array::displayArray()
{
    std::string str;     // ��̕�������쐬
    for (cArray::Iterator it(ary); !it.end(); it++) {
        cMessage *msg = check_and_cast<cMessage *>(*it);
        str += "," + std::to_string(msg->getKind());    // ���҂�J���e�̘A�Ԃ��L
    }
    str.erase(0,1);     // �擪�������폜
    getDisplayString().setTagArg("t", 0, str.c_str());  // �V�~�����[�V������ʂɕ\��
}

//�@�m�[�h�̓��v����\��
void Array::finish()
{
    EV << qName << " AVG Length:   " << qlen.get(simTime()) << endl;
    EV << qName << " Jobs Count:   " << stats.getCount() << endl;
    EV << qName << " Min WaitTime: " << stats.getMin() << endl;
    EV << qName << " Avg WaitTime: " << stats.getMean() << endl;
    EV << qName << " Max WaitTime: " << stats.getMax() << endl;
    EV << qName << " Standard deviation: " << stats.getStddev() << endl;
}
