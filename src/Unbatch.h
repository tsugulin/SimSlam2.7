#ifndef UNBATCH_H_
#define UNBATCH_H_

#include <omnetpp.h>
using namespace omnetpp;

class Unbatch : public cSimpleModule
{
private:
    cStdDev stats;

protected:
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* UNBATCH_H_ */
