/*
 * socket.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef SOCKET_H_2013_7_31
#define SOCKET_H_2013_7_31

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
#include <errno.h>
#include "utils.h"

namespace Sockets
{
  using namespace std;

  void SetSockAddr(sockaddr_in &addr, uint16_t port, const char* pszIp)
  {
    ::bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port);
    addr.sin_addr.s_addr = pszIp ? ::inet_addr(pszIp) // prefer inet_aton to inet_addr
                                 : ::htonl(INADDR_ANY);
  }

  int Create(int type, int protocol=0)
  {
    int sockfd = ::socket(AF_INET, type, protocol);
    ASSERT_IF(-1==sockfd, "socket");
    return sockfd;
  }

  int Bind(int sockfd, uint16_t port, const char* pszLocalIp=NULL)
  {
    sockaddr_in localAddr;
    SetSockAddr(localAddr, port, pszLocalIp);
    int ret = ::bind(sockfd, (sockaddr*)&localAddr, sizeof(localAddr));
    ASSERT_IF(-1==ret, "bind");
    return ret;
  }

  int Bind(int sockfd, sockaddr_in &localAddr)
  {
    int ret = ::bind(sockfd, (sockaddr*)&localAddr, sizeof(localAddr));
    ASSERT_IF(-1==ret, "bind");
    return ret;
  }

  int Listen(int sockfd, int backlog=100)
  {
    int ret = ::listen(sockfd, backlog);
    ASSERT_IF(-1==ret, "listen");
    return ret;
  }

  int SetSockOpt(int sockfd, int level, int optname, void* optval, socklen_t optlen)
  {
    int ret = ::setsockopt(sockfd, level, optname, optval, optlen);
    ASSERT_IF(-1==ret, "setsockopt");
    return ret;
  }

  int Accept(int listenSock, sockaddr_in &ClientAddr)
  {
    socklen_t addrlen = sizeof(sockaddr_in);
    int connSockfd = ::accept(listenSock, (sockaddr*)&ClientAddr, &addrlen);
    ASSERT_IF(-1==connSockfd, "accept");
    return connSockfd;
  }

  int SetBlocking(int sockfd, bool bBlock)
  {
    int flags = ::fcntl(sockfd, F_GETFL);
    ASSERT_IF(-1==flags, "fcntl");

    if(bBlock)
    {
      flags &= ~O_NONBLOCK;
    }
    else
    {
      flags |= O_NONBLOCK;
    }

    int ret = ::fcntl(sockfd, F_SETFL, flags);
    ASSERT_IF(-1==ret, "fcntl");
    return ret;
  }

  int SetReuseAddr(int sockfd, bool bSet)
  {
    int optval = bSet ? 1:0;
    return SetSockOpt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  }

  void Read(int sockfd, string &msg)
  {
    msg.clear();

    char buf[1024] = {0};
    int nReceived = 0;
    while ( -1 != (nReceived=::recv(sockfd, buf, sizeof(buf), 0)) )
    {
      if(EWOULDBLOCK != errno)
      {
        assert(false);
      }

      if(0 == nReceived)
        break;

      msg.append(buf, nReceived);
    }
  }

}// namespace Socket end


#endif /* SOCKET_H_2013_7_31 */
