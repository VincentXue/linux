/*
 * Poller.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#include "Poller.h"
#include <unistd.h>
#include "utils.h"

using namespace std;

Poller::Poller()
  : _epollfd(-1)
  , _bCreateOK(false)
{

}

Poller::~Poller()
{
  if(_bCreateOK)
  {
    ::close(_epollfd);
  }
}

bool Poller::Create()
{
  if(!_bCreateOK)
  {
    _epollfd = ::epoll_create(100);
    ASSERT_IF(-1==_epollfd, "epoll_create");
    _bCreateOK = (_epollfd==-1) ? false : true;
  }
  return _bCreateOK;
}

bool Poller::Register(int fd, int eventMask, void* p)
{
  epoll_event e;
  e.events = eventMask;
  e.data.ptr = p;
  int ret = ::epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &e);
  ASSERT_IF(-1==ret, "epoll_ctl");
  return -1!=ret;
}

bool Poller::Unregister(int fd)
{
  epoll_event e;
  int ret = ::epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, &e);
  ASSERT_IF(-1==ret, "epoll_ctl");
  return -1!=ret;
}

bool Poller::WaitEvents(vector<epoll_event> &vecEvents, int timeout/*=-1*/)
{
  vecEvents.clear();

  epoll_event aryEvents[100];
  int nEvents =
      ::epoll_wait(_epollfd, aryEvents, _COUNT_OF(aryEvents), timeout);
  ASSERT_IF(-1==nEvents, "epoll_wait");
  for (int i=0; i<nEvents; i++)
  {
    vecEvents.push_back(aryEvents[i]);
  }

  return -1!=nEvents;
}
