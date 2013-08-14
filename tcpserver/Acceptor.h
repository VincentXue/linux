/*
 * Acceptor.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "IEventHandler.h"

class IAcceptHandler;
class Poller;

class Acceptor : public IEventHandler
{
public:
  Acceptor(Poller *pPoller, uint16_t port, const char* pszLocalIp=NULL);
  virtual ~Acceptor();

  void SetAcceptHandler(IAcceptHandler *pHandler);
  bool StartListen(int backlog);

  void SetOccuredEvents(int events);
  int OnEvent();
  int OnIn();


private:
  int               _listenfd;
  Poller*           _pPoller;
  sockaddr_in       _localAddr;
  int               _occuredEvents;
  IAcceptHandler*   _pAcceptHandler;
};

#endif /* ACCEPTOR_H_ */
