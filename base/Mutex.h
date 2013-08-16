/*
 * Mutex.h
 *
 *  Created on: Aug 15, 2013
 *      Author: leo
 */

#ifndef MUTEX_H_2013_8_15_
#define MUTEX_H_2013_8_15_

#include <pthread.h>

class Mutex
{
public:
  Mutex();
  ~Mutex();

  bool Lock();
  bool Unlock();

private:
  pthread_mutex_t           _mutexp;
  pthread_mutexattr_t       _mutexAttr;
};


class MutexLock
{
public:
  MutexLock(Mutex &m);
  ~MutexLock();

private:
  Mutex&                    _mutex;
};

#endif /* MUTEX_H_ */
