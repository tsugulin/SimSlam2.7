#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"
#define maxQnum 100

class Match;

class BlockingQueue : public cSimpleModule
{
  private:
    const char *qName;
    bool onActivity;
    bool matchNode;
    cQueue queue;
    Match *next;
    Wavg qlen;
    cStdDev stats;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    virtual void startActivity();
};

#endif /* BLOCKINGQUEUE_H_ */
