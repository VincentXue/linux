#ifndef _IEVENT_HANDLER_2013_7_31_
#define _IEVENT_HANDLER_2013_7_31_

class IEventHandler
{
public:
  virtual ~IEventHandler() {}

  virtual void SetOccuredEvents(int events) = 0;
  virtual int OnEvent() = 0;
};


#endif //_IEVENT_HANDLER_2013_7_31_
