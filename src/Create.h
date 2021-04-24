#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Create : public cSimpleModule {
private:
  cMessage *beatMsg;    // 繰り返し利用するメッセージを１つだけ作成

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif /* CREATE_H_ */
