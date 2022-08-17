#pragma once

#include "Arduino.h"
#include "WiFi.h"

#define ssid      "office1"
#define password  "qwer1234!@#$"

// IR_Routine.cpp
extern void InitIr();
extern void RecvLoop();
extern void SendNecTest();

// GetTime.cpp
extern boolean diff(unsigned long now, unsigned long prev, unsigned long d);
extern void UpdateLocalTime();
extern int* GetTimeForUserset();

extern unsigned long long now;