#include "Recv_IR.h"

void RecvSet()
{
  recv.enableIRIn();
  recv.blink13(true);
}

void RecvLoop()
{
  if (recv.decode(&results))
  {
        Serial.println(results.value, HEX);
        recv.resume();
  }
}