#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Create : public cSimpleModule {
private:
  cMessage *beatMsg;    // �J��Ԃ����p���郁�b�Z�[�W���P�����쐬

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif /* CREATE_H_ */
