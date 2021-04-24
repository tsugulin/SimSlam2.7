#include "Batch.h"
Define_Module(Batch);

void Batch::initialize()
{
    imax = par("workUnit");         // �o�b�`�ɂďW�񂷂��
    idx = 0;                        // �A�Ԃ�������
    msgs = new cQueue("msgs");       // �I�u�W�F�N�g�𐶐�
    batch = new cMessage("batch");  // �o�b�`���b�Z�[�W�̍쐬
}

void Batch::handleMessage(cMessage *msg)
{
    // �O�H������͂������b�Z�[�W�̏ꍇ�C�A�N�e�B�r�e�B���J�n
    msgs->insert(msg);          // �o�b�`�Ƀ��b�Z�[�W��ǉ�
    if (++idx >= imax) {
        // �K�v�����܂����ꍇ
        batch->addObject(msgs);         // ���b�Z�[�W�ɑ҂��s���ǉ�
        send(batch, "out");             // ���H���Ƀo�b�`���b�Z�[�W�𑗐M
        idx = 0;                        // �A�Ԃ�������
        msgs = new cQueue("msgs");       // �I�u�W�F�N�g�𐶐�
        batch = new cMessage("batch");  // �o�b�`���b�Z�[�W�̍쐬
        stats.collect(0);               // ���M�����L�^
    }
}

//�@����������\��
void Batch::finish()
{
    EV << "Batch jobs Count: " << stats.getCount() << endl;
    delete msgs;
    delete batch;
}
