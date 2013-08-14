/*
 * TcpServer.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <unistd.h>
class Poller;

class TcpServer : public IAcceptHandler
{
public:
  TcpServer(int port, const char* pszLocalIp=NULL);
  virtual ~TcpServer();

  virtual int OnAccept(int connfd, const sockaddr_in &clientAddr);

private:
  Poller*           _pPoller;
};

#endif /* TCPSERVER_H_ */
