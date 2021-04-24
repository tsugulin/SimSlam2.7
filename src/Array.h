#ifndef ARRAY_H_
#define ARRAY_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"
#define maxQnum 100

class Match;

class Array : public cSimpleModule
{
private:
    const char *qName;
    cArray ary;
    long length;  // 保管しているメッセージ数
    Match *next;
    Wavg qlen;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void startActivity(long);
    virtual void displayArray();

public:
    virtual bool check(long);
    virtual void remove(long);
};

#endif /* ARRAY_H_ */
