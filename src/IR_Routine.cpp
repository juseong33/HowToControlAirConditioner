#include "IR_Routine.h"

unsigned long past = 0;
AcCommands CheckAc;
int IfLoop = 1;

void InitIr()
{
  IrReceiver.begin(RECV_PIN, true);
  IrSender.begin(SEND_PIN, true);
  CheckAc.Onoff = true;
  CheckAc.Init = true;
  CheckAc.Water = false;
}

// IR 신호 수신
void RecvLoop()
{
  if (IrReceiver.decode())
  {
    if ((IrReceiver.decodedIRData.decodedRawData != 0xFFFFFFFF) && (IrReceiver.decodedIRData.decodedRawData != 0x00000000)) // 노이즈 발생 시 출력하지 않음
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
  IrSender.sendNECRaw(IrMode, 0);
  delay(2000);
  IrSender.sendNECRaw(IrMode, 0);
  delay(2000);
  IrSender.sendNECRaw(IrMode, 0);
  delay(2000);
  IrSender.sendNECRaw(IrMode, 0);
}
void DayTimeRoutine() // 2022-10-05 Changed
{
  // 전원 가동 후(냉방모드) 15분이 지나면 10분 쉼
  if ((now - past >= 900000) && (IfLoop == 1))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "전원Off");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
  // 전원 Off 후 10분이 지나면 송풍모드
  if ((now - past >= 600000) && (IfLoop == 2))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "송풍모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 0);
  }
  // 송풍 모드 후 10분이 지나면 Auto모드
  if ((now - past >= 600000) && (IfLoop == 3))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "Auto모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrMode, 0);
  }
  // Auto모드 후 15분이 지나면 쉼
  if ((now - past >= 900000) && (IfLoop == 4))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "전원Off");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
  // 전원 Off 후 10분이 지나면 냉방모드
  if ((now - past >= 600000) && (IfLoop == 5))
  {
    past = now;
    IfLoop = 1;
    strcpy(CheckAc.Mode, "냉방모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 0);
  }
}

/*
void DayTimeRoutine()
{
  // 전원 가동 후 20분이 지나면 송풍모드 == 20분동안 냉방모드
  if ((now - past >= 1200000) && (IfLoop == 1))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "송풍모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrMode, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 0);
  }
  // 송풍모드 가동 후 20분이 지나면 Auto모드 == 20분동안 송풍모드
  if ((now - past >= 1200000) && (IfLoop == 2))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "Auto모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrMode, 0);
  }
  // Auto모드 가동 후 10분이 지나면 전원 Off = 10분동안 Auto모드
  if ((now - past >= 600000) && (IfLoop == 3))
  {
    past = now;
    ++IfLoop;
    strcpy(CheckAc.Mode, "전원Off");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
  // 전원 Off 후 10분이 지나면 냉방모드 전원 On = 10분동안 전원 Off
  if ((now - past >= 600000) && (IfLoop == 4))
  {
    past = now;
    IfLoop = 1;
    strcpy(CheckAc.Mode, "냉방모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
    delay(2000);
    IrSender.sendNECRaw(IrMode, 0);
  }
}
*/

// Evening 루틴으로 넘어가기 전 현재모드 체크
void CheckMode()
{
  // Daytime 루틴인지 첫번째 확인
  if (CheckAc.Sunrise == true)
  {
    // 송풍모드나 전원이 꺼진 상태면 바로 Evening 루틴으로 넘김
    if (((strcmp(CheckAc.Mode, "송풍모드") == 0) && (CheckAc.Onoff == true)) || ((strcmp(CheckAc.Mode, "전원Off") == 0) && (CheckAc.Onoff == false)))
    {
      Serial.println("Go To EveningRoutine");
      CheckAc.Sunrise = false;
    }
    // 냉방모드면 송풍모드로 변경 후 Evening 루틴으로 넘김
    else if ((strcmp(CheckAc.Mode, "냉방모드") == 0) && (CheckAc.Onoff == true))
    {
      Serial.println("Mode Changed, Go To EveningRoutine");
      IrSender.sendNECRaw(IrMode, 0);
      delay(2000);
      IrSender.sendNECRaw(IrMode, 0);
      strcpy(CheckAc.Mode, "송풍모드");
      CheckAc.Sunrise = false;
    }
  }
  delay(1000);
}

// 오후 7시 ~ 오전 9시까지의 루틴
void EveningRoutine()
{
  // 송풍모드로 넘어왔을 시 20분 뒤 전원을 끔, DayTime루틴의 3번째 if문으로 이동
  if ((now - past >= 1200000) && (strcmp(CheckAc.Mode, "송풍모드") == 0) && (CheckAc.Sunrise == false))
  {
    past = now;
    CheckAc.Onoff = false;
    strcpy(CheckAc.Mode, "전원Off");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
  // 전원 Off로 넘어왔을 시 20분뒤 전원을 킴, DayTime루틴의 2번째 if문으로 이동
  if ((now - past >= 1200000) && (strcmp(CheckAc.Mode, "전원Off") == 0) && (CheckAc.Sunrise == false))
  {
    past = now;
    CheckAc.Onoff = true;
    CheckAc.Init = false;
    strcpy(CheckAc.Mode, "송풍모드");
    Serial.println(CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
  }
}

// 수위센서가 감지되었을 때 동작
void WaterDetect()
{
  // 전원이 꺼져있는 상태에서 감지
  if ((WaterSensorVal != 0) && (strcmp(CheckAc.Mode, "전원Off") == 0) && (CheckAc.Water == false))
  {
    CheckAc.Water = true;
    Serial.printf("수위센서가 감지되어 루틴을 보류합니다. (현재모드 : %s)\n", CheckAc.Mode);
    send_event("Water_Detect");
  }
  // 전원이 켜져있는 상태에서 감지
  if ((WaterSensorVal != 0) && (strcmp(CheckAc.Mode, "전원Off") != 0) && (CheckAc.Water == false))
  {
    CheckAc.Water = true;
    CheckAc.Onoff = false;
    Serial.printf("수위센서가 감지되어 루틴을 보류합니다. (현재모드 : %s)\n", CheckAc.Mode);
    IrSender.sendNECRaw(IrPower, 0);
    send_event("Water_Detect");
  }
}

void BackToRoutine()
{
  if (WaterSensorVal == 0 && CheckAc.Water == true)
  {
    CheckAc.Water = false;
    CheckAc.Onoff = true;
    IrSender.sendNECRaw(IrPower, 0);
    Serial.println("루틴을 재개합니다.");
  }
}