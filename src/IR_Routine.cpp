#include "IR_Routine.h"

unsigned long long past = 0;
AcCommands CheckAc;

void InitIr()
{
  IrReceiver.begin(RECV_PIN, true);
  IrSender.begin(SEND_PIN, true);
  CheckAc.Onoff = true;
  CheckAc.Init = true;
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
    Serial.println("Test For Successful NEC Reception");
    IrSender.sendNECRaw(IrMode, 4);
}

// 오전 9시 ~ 오후 7시까지의 루틴
void DayTimeRoutine()
{
  CheckAc.Sunrise = true;
  // 전원 가동 후 17분이 지나면 송풍모드 == 17분 동안 냉방모드
  if ((now - past >= 1000 /*MinToMils(17)*/) && (CheckAc.Onoff == true) && (CheckAc.Init == true) && (CheckAc.Sunrise == true))
  {
    past = now;
    CheckAc.Init = false;
    strcpy(CheckAc.Mode, "송풍모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrMode, 2);
  }
  // 송풍 모드 17분 가동 후 전원 OFF
  if ((now - past >= 1000 /*MinToMils(17)*/) && (CheckAc.Onoff == true) && (CheckAc.Init == false) && (CheckAc.Sunrise == true))
  {
    past = now;
    CheckAc.Onoff = false;
    strcpy(CheckAc.Mode, "전원 Off");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
  // 전원이 꺼진 25분 후 전원을 킨 뒤, 냉방모드로 전환
  if ((now - past >= 1000 /*MinToMils(17)*/) && (CheckAc.Onoff == false) && (CheckAc.Init == false) && (CheckAc.Sunrise == true))
  {
    past = now;
    CheckAc.Onoff = true;
    CheckAc.Init = true;
    strcpy(CheckAc.Mode, "냉방모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 2);
  }
}

// 오후 7시 ~ 오전 9시까지의 루틴
void EveningRoutine()
{

}