#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Lockup;

class Resource : public cSimpleModule {
private:
    long owner;
    simtime_t checkpoint;
    Lockup *node;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void finish();
    virtual void displayArray(bool);

public:
    virtual bool request(long);
    virtual bool release(long);
};

#endif /* RESOURCE_H_ */
