/*
 * Connection.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

class Poller;
class Connection : IEventHandler
{
public:
  Connection(Poller *pPoller, int connfd, const sockaddr_in &peerAddr);
  virtual ~Connection();

  void RegisterReadEvent();

  virtual void SetOccuredEvents(int events);
  virtual int OnEvent();

  int OnIn();

private:
  Poller*       _pPoller;
  int           _connfd;
  sockaddr_in   _peerAddr;
  int           _occuredEvents;
};

#endif /* CONNECTION_H_ */
