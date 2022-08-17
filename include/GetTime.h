#pragma once

#include "Common.h"
#include "time.h"

#define MAX 0xFFFFFFFF

struct tm *glb_ptm;
struct timeval glb_curTime;
time_t glb_rawtime;

const char NTP_SERVER[] = "pool.ntp.org";
const char TIME_ZONE = 9;

boolean diff(unsigned long now, unsigned long prev, unsigned long d);
void UpdateLocalTime();
int* GetTimeForUserset();
int MinToMils(uint8_t Min);