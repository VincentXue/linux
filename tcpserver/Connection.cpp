/*
 * Connection.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#include "Connection.h"
#include "Poller.h"
#include <assert.h>
#include <string>
#include <cstdio>
#include <netinet/in.h>

using namespace std;

Connection::Connection(Poller *pPoller, int connfd, const sockaddr_in &peerAddr)
  : _pPoller(pPoller)
  , _connfd(connfd)
  , _peerAddr(peerAddr)
  , _occuredEvents(0)
{
}

Connection::~Connection()
{
  if(-1 != _connfd)
  {
    ::close(_connfd);
  }
}

void Connection::RegisterReadEvent()
{
  assert(_pPoller);
  _pPoller->Register(_connfd, EPOLLIN, this);
}

void Connection::SetOccuredEvents(int events)
{
  _occuredEvents = events;
}

int Connection::OnEvent()
{
  int ret = 0;
  if(_occuredEvents & EPOLLIN)
  {
    ret = OnIn();
  }
  return ret;
}

int Connection::OnIn()
{
  string msg;
  Sockets::Read(_connfd, msg);

  if(0 == msg.size())
  {
    _pPoller->Unregister(_connfd); // the other end closed connection
    ::close(_connfd);
    _connfd = -1;
  }
  else
  {
    printf(msg.c_str());
  }

}
