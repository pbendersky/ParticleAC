#ifndef IRSenderIRRemoteBridge_h
#define IRSenderIRRemoteBridge_h

#include <IRremote.h>
#include <IRSender.h>

class IRSenderIRRemoteBridge : public IRSender
{
  IRsend irSend;
  
  public:
    IRSenderIRRemoteBridge();
    void setFrequency(int frequency);
    void space(int spaceLength);
    void mark(int markLength);
};

#endif // ifndef IRSenderIRRemoteBridge_h