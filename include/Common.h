#pragma once

#include "Arduino.h"
#include "WiFi.h"
#include <string.h>

// IR_Routine.cpp
extern void InitIr();
extern void RecvLoop();
extern void SendNecTest();
extern void DayTimeRoutine();
extern void EveningRoutine();
extern void CheckMode();
extern void WaterDetect();
extern void BackToRoutine();

// GetTime.cpp
extern boolean diff(unsigned long now, unsigned long prev, unsigned long d);
extern void UpdateLocalTime();
extern int *GetTimeForUserset();
extern int MinToMils(uint8_t Min);

// Wifis.h
extern void send_event(const char *event);
extern void Wifi_Init();

extern unsigned long now;
extern uint16_t WaterSensorVal;