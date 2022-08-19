#pragma once

#include "Common.h"
#include "IRremote.h"

#define IrPower 0x7F20DF // Remote Power On/Off
#define IrUp 0x7FA05F    // Remote Temp up
#define IrDown 0x7F609F  // Remote Temp down
#define IrMode 0x7F00FF  // Remote Mode change

typedef struct _AcCommands
{
  bool Onoff;    // True : 에어컨의 전원 On, False : 에어컨의 전원 Off
  bool Init;     // True : 함수의 첫 If문,   False : 함수의 첫 If문이 아님
  bool Sunrise;  // True : DayTime,          False : Evening
  bool Water;    // True : 물 감지,          False : 물 감지되지 않음
  char Mode[20]; // 현재모드 문자열 저장
} AcCommands;
/*
 * 신일 리모컨 분석 코드 결과 *
 * 전원 : 7F20DF
 * + : 7FA05F
 * - : 7F609F
 * 바람세기 : 7FE01F
 * 시간조절 : 7F807F
 * 수면 : 7FC03F
 * 모드 : 7F00FF
 */
const uint16_t SEND_PIN = 13U;
const uint16_t RECV_PIN = 14U;

void InitIr();
void RecvLoop();
void SendNecTest();
void DayTimeRoutine();
void EveningRoutine();
void CheckMode();
void WaterDetect();