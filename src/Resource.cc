#include "Resource.h"
Define_Module(Resource);
#include "Lockup.h"

void Resource::initialize()
{
    // �ϐ���������
    owner = 0;   // ������

    // Await�m�[�h�̃|�C���^���擾
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    node = check_and_cast<Lockup *>(mod);
}

// ���\�[�X�̊l�����s��
bool Resource::request(long id)
{
    Enter_Method("request");
    bool ret_code = false;          // �߂�l��������
    if ( owner == 0 ) {
        owner = id;                 // �������\�[�X�����g�p�ł���Ηv���҂����p�\�Ƃ���
        displayArray(true);         // ���\�[�X�g�p��
        checkpoint = simTime();     // ���\�[�X�l���������L�^
        ret_code = true;            // ���\�[�X�l���ɐ���
    }
    return ret_code;    // ���\�[�X�l���ł����true��߂�
}

// ���\�[�X�̉�����s��
bool Resource::release(long id)
{
    Enter_Method("release");
    bool ret_code = false;          // �߂�l��������
    if ( owner == id ) {
        owner = 0;                  // ���\�[�X�����
        displayArray(false);        // ���\�[�X���g�p
        stats.collect( simTime() - checkpoint );    // ���\�[�X�g�p���Ԃ��L�^
        node->goForward();     // ���̃��b�Z�[�W�̃��\�[�X���m�ۂ���
        ret_code = true;            // ���\�[�X����ɐ���
    }
    return ret_code;    // ���\�[�X����ł����true��߂�
}

// �V�~�����[�V�������s��ʂ̃A�C�R���ɑ҂��󋵂�\������
void Resource::displayArray(bool flag)
{
    if (flag)
        getDisplayString().setTagArg("t", 0, "Now Using");
    else
        getDisplayString().setTagArg("t", 0, "Now Available");
}

void Resource::finish()
{
    EV << "Resource jobs Count:  " << stats.getCount() << endl;
    EV << "Resource Utilization: " << stats.getSum() / simTime() << endl;
}
