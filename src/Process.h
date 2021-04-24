#ifndef PROCESS_H_
#define PROCESS_H_

#include <omnetpp.h>
using namespace omnetpp;

class Resource;

class Process : public cSimpleModule {
private:
    Resource *rsc;      // ���\�[�X�̃|�C���^
    cMessage *self;     // ���\�[�X����p�̃��b�Z�[�W
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* PROCESS_H_ */
