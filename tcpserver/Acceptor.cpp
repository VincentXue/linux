/*
 * Acceptor.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#include "Acceptor.h"
#include <strings.h>
#include <sys/socket.h>
#include <cstdio>
//#include <sys/types.h>
#include "Poller.h"
#include "sockets.h"
#include "IAcceptHandler.h"

Acceptor::Acceptor(Poller *pPoller, uint16_t port, const char* pszLocalIp/*=NULL*/)
  : _listenfd(-1)
  , _pPoller(pPoller)
  , _occuredEvents(0)
  , _pAcceptHandler(NULL)
{
  Sockets::SetSockAddr(_localAddr, port, pszLocalIp);
}

Acceptor::~Acceptor()
{
}

void Acceptor::SetAcceptHandler(IAcceptHandler* pHandler)
{
  _pAcceptHandler = pHandler;
}

bool Acceptor::StartListen(int backlog)
{
  assert(_pAcceptHandler);

  if(-1 == _listenfd)
  {
    _listenfd = Sockets::Create(SOCK_STREAM);
  }

  Sockets::SetReuseAddr(_listenfd, true);
  Sockets::SetBlocking(_listenfd, false);
  Sockets::Bind(_listenfd, _localAddr);
  Sockets::Listen(_listenfd, backlog);

  assert(_pPoller);
  return _pPoller->Register(_listenfd, EPOLLIN, this);
}

void Acceptor::SetOccuredEvents(int events)
{
  _occuredEvents = events;
}

int Acceptor::OnEvent()
{
  if(_occuredEvents & EPOLLIN)
  {
    OnIn();
  }
  return 0;
}

int Acceptor::OnIn()
{
  sockaddr_in clientAddr;
  int connfd = Sockets::Accept(_listenfd, clientAddr);
  return _pAcceptHandler->OnAccept(connfd, clientAddr);
}
