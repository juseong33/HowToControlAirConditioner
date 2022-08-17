#include "IR_Routine.h"

unsigned long long past = 0;

void InitIr()
{
  IrReceiver.begin(RECV_PIN, true);
  IrSender.begin(SEND_PIN, true);
}

// IR 신호 수신
void RecvLoop()
{
  if (IrReceiver.decode())
  {
    if(IrReceiver.decodedIRData.decodedRawData != 0xFFFFFFFF && IrReceiver.decodedIRData.decodedRawData != 0x00000000)   // 노이즈 발생 시 출력하지 않음
    {
      Serial.print("Receive Data: ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    }
    IrReceiver.resume();
  }
}

// 시스템이 정상적으로 신호를 수신하는지 확인하기 위함
void SendNecTest()
{
  for (uint8_t i = 0; i < 4; i++)
  {
    Serial.println("Test For Successful NEC Reception");
    IrSender.sendNECRaw(Power, 0);
    delay(2000);
  }
}