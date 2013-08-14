/*
 * TcpServer.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#include "TcpServer.h"
#include <cstdio>

TcpServer::TcpServer(int port, const char* pszLocalIp)
  : _pPoller(NULL)
{

}

TcpServer::~TcpServer()
{

}

int TcpServer::OnAccept(int connfd, const sockaddr_in& clientAddr)
{
  Sockets::SetBlocking(connfd, false);
  return 0;
}
