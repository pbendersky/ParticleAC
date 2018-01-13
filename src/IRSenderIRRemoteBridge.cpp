#include <Arduino.h>
#include <IRSender.h>
#include <IRremote.h>

#include "IRSenderIRRemoteBridge.h"

IRSenderIRRemoteBridge::IRSenderIRRemoteBridge() : IRSender(D3)
{
  irSend = IRsend();
}

void IRSenderIRRemoteBridge::setFrequency(int frequency)
{
  irSend.enableIROut(frequency);
}

void IRSenderIRRemoteBridge::mark(int time)
{
  irSend.mark(time);
}

void IRSenderIRRemoteBridge::space(int time)
{
  irSend.space(time);
}