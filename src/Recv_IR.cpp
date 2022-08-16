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
    if(results.value != 0xFFFFFFFF)   // 노이즈 발생 시 출력하지 않음
    {
      Serial.print("Receive Data: ");
      Serial.println(results.value, HEX);
    }
    recv.resume();
  }
}