#pragma once

#include "Common.h"
#include "IRremote.h"

#define IrPower 0xFB04FE00 // Remote Power On/Off
#define IrUp    0xFA05FE00    // Remote Temp up
#define IrDown  0xF906FE00  // Remote Temp down
#define IrMode  0xFF00FE00  // Remote Mode change

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
 * 전원 : FB04FE00
 * + : FA05FE00
 * - : F906FE00
 * 바람세기 : F807FE00
 * 시간조절 : FE01FE00
 * 수면 : FC03FE00
 * 모드 : FF00FE00 
 */
const uint16_t SEND_PIN = 14U;
const uint16_t RECV_PIN = 13U;

void InitIr();
void RecvLoop();
void SendNecTest();
void DayTimeRoutine();
void EveningRoutine();
void CheckMode();
void WaterDetect();
void BackToRoutine();