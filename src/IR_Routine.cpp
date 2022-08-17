#include "IR_Routine.h"

void RecvSet()
{
  IrReceiver.begin(RECV_PIN, true);
  IrSender.begin(SEND_PIN, true);
}

void RecvLoop()
{
  if (IrReceiver.decode())
  {
    if(IrReceiver.decodedIRData.decodedRawData != 0xFFFFFFFF)   // 노이즈 발생 시 출력하지 않음
    {
      Serial.print("Receive Data: ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    }
    IrReceiver.resume();
  }
}

void SendNecTest()
{
  IrSender.sendNECRaw(Power, 0);
  //Serial.println("Power");
  delay(2000);
}