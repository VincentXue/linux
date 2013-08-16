/*
 * Mutex.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: leo
 */

#include "Mutex.h"
#include <errno.h>

Mutex::Mutex()
  : _mutexp(PTHREAD_MUTEX_INITIALIZER)
{
}

Mutex::~Mutex()
{
}

bool Mutex::Lock()
{
  int ret = pthread_mutex_lock(&_mutexp);
  if(0 != ret) {
    errno = ret;
  }
  return 0==ret;
}

bool Mutex::Unlock()
{
  int ret = pthread_mutex_unlock(&_mutexp);
  if(0 != ret) {
    errno = ret;
  }
  return 0==ret;
}


MutexLock::MutexLock(Mutex& m)
  :_mutex(m)
{
  _mutex.Lock();
}

MutexLock::~MutexLock()
{
  _mutex.Unlock();
}
