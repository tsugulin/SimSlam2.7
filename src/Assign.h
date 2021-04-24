#ifndef ASSIGN_H_
#define ASSIGN_H_

#include <omnetpp.h>
using namespace omnetpp;

class Assign : public cSimpleModule
{
private:
    long kind;
    cStdDev stats1;
    cStdDev stats2;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* ASSIGN_H_ */
