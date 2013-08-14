#ifndef _TIME_COUNTER_H_2013_8_14_
#define _TIME_COUNTER_H_2013_8_14_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <strings.h>

#define CLOCK_ID CLOCK_MONOTONIC_RAW

static timespec _tBegin;
static char _szName[256] = {0};

inline void tick_begin(const char* pszName) {
  bzero(_szName, sizeof(_szName));
  strncpy(_szName, pszName?pszName:"unknow", sizeof(_szName)-1);
  clock_gettime(CLOCK_ID, &_tBegin);
}


inline void tick_end() {
  timespec tEnd;
  clock_gettime(CLOCK_ID, &tEnd);
  double timeInterval = tEnd.tv_sec-_tBegin.tv_sec+(tEnd.tv_nsec-_tBegin.tv_nsec)/1000000000.0;
  printf("%.9lfs is costed by %s\n", timeInterval, _szName);
}


#endif //_TIME_COUNTER_H_2013_8_14_
