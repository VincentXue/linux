#ifndef _UTILS_BY_XGF_2013_7_29_
#define _UTILS_BY_XGF_2013_7_29_

#include <assert.h>
#include <stdio.h>

#define _COUNT_OF(ary) (sizeof(ary)/sizeof(ary[0]))

#define ASSERT_IF(exp, prompt)\
  do{\
    if(exp){\
      assert(!(exp));\
      perror(prompt);\
    }\
  }while(0)


#define SAFE_DELETE(p)\
  do{\
    delete p;\
    p = NULL;\
  }while(0)


#endif //_UTILS_BY_XGF_2013_7_29_
