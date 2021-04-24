#ifndef LOCKUP_H_
#define LOCKUP_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"

class Resource;

class Lockup : public cSimpleModule {
private:
    cQueue queue;
    Wavg qlen;
    Resource *rsc;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

public:
    virtual void goForward();
};

#endif /* LOCKUP_H_ */
