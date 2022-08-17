#pragma once

#include "Common.h"
#include "IRremote.h"

#define IrPower 0x7F20DF // Remote Power On/Off
#define Up 0x7FA05F    // Remote Temp up
#define Down 0x7F609F  // Remote Temp down
#define IrMode 0x7F00FF  // Remote Mode change

typedef struct _AcCommands {
  bool Onoff;
  bool Init;
  bool Sunrise;
  char Mode[20];
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