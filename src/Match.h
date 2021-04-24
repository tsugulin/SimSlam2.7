#ifndef MATCH_H_
#define MATCH_H_

#include <omnetpp.h>
using namespace omnetpp;

class Array;

class Match : public cSimpleModule
{
private:
    cModule *mod1;
    cModule *mod2;
    Array *before1;
    Array *before2;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

public:
    virtual bool check(long);
};

#endif /* MATCH_H_ */
