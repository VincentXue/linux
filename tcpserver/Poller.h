/*
 * Poller.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef POLLER_H_
#define POLLER_H_

#include <sys/epoll.h>
#include <vector>

class Poller
{
public:
  Poller();
  virtual ~Poller();

  bool Create();
  bool Register(int fd, int eventMask, void* p);
  bool Unregister(int fd);
  bool WaitEvents(std::vector<epoll_event> &vecEvents, int timeout=-1);

private:
  int           _epollfd;
  int           _bCreateOK;
};

#endif /* POLLER_H_ */
