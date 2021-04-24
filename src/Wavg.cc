#include "Wavg.h"

Wavg::Wavg()
{
    start = SIMTIME_ZERO;
    checkpoint = start;
    size = 0;
}

Wavg::~Wavg()
{
    if (size > 0) delete[] length;
}

void Wavg::init(simtime_t t, int n)
{
    if (n > 0) {
        start = t;                      // �J�n�������Z�b�g
        checkpoint = start;             // �J�n�������Z�b�g
        size = n;                       // �z��T�C�Y
        length = new double[size];      // �L���[�̒������Z�b�g
        for (int i = 0;  i <= n;  i++)  // �z�񏉊���
            length[i] = 0;
    } else {
        EV << "Memory Allocation Error!" << endl;
    }
}

void Wavg::set(simtime_t t, int n)
{
    simtime_t_cref d = t - checkpoint;  // �O�񂩂�̌o�ߎ��Ԃ��Z�o
    checkpoint = t;                     // �o�ߎ��Ԃ��N���A
    length[n] += d.dbl();               // ���ϑ҂��s�񒷂���ۊ�
}

double Wavg::get(simtime_t t)
{
    double a = 0;                       // ���d���ϒl��������
    for (int i = 0;  i <= size;  i++)   // �e�z��ɏd�݂����Z�i�����q�j
        a += length[i] * i;
    simtime_t_cref d = t - start;       // �S�̂̎��Ԃ��v�Z�i������j
    a = a / d.dbl();                    // ���d���ϒl���v�Z�i���q������j
    return(a);
}
