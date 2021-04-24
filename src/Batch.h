#ifndef BATCH_H_
#define BATCH_H_

#include <omnetpp.h>
using namespace omnetpp;

class Batch : public cSimpleModule {
private:
    long imax;          // インデックスの最大値
    long idx;           // メッセージ配列のインデックス
    cQueue *msgs;
    cMessage *batch;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* BATCH_H_ */
