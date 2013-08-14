/*
 * IAcceptHandler.h
 *
 *  Created on: Jul 31, 2013
 *      Author: leo
 */

#ifndef IACCEPTHANDLER_H_2013_7_31
#define IACCEPTHANDLER_H_2013_7_31

class IAcceptHandler
{
public:
  ~IAcceptHandler() {}

  virtual int OnAccept(int connfd, const sockaddr_in &clientAddr) = 0;
};


#endif /* IACCEPTHANDLER_H_2013_7_31 */
