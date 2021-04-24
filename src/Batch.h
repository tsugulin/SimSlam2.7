#ifndef BATCH_H_
#define BATCH_H_

#include <omnetpp.h>
using namespace omnetpp;

class Batch : public cSimpleModule {
private:
    long imax;          // �C���f�b�N�X�̍ő�l
    long idx;           // ���b�Z�[�W�z��̃C���f�b�N�X
    cQueue *msgs;
    cMessage *batch;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* BATCH_H_ */
