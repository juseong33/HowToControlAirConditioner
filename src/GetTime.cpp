#include "GetTime.h"

// 타이머 IF문 구성 함수 & 오버플로우 방지
boolean diff(unsigned long now, unsigned long prev, unsigned long d)
{
  if (now > prev)
  {
    return ((now - prev) >= d);
  }
  else
  {
    return (((MAX - prev) + now + 1) >= d);
  }
}

void UpdateLocalTime()
{
  configTime(3600 * TIME_ZONE, 0, NTP_SERVER);
  gettimeofday(&glb_curTime, NULL);
}

int *GetTimeForUserset()
{
  UpdateLocalTime();
  time(&glb_rawtime);
  glb_ptm = localtime(&glb_rawtime);

  int hh = 0;
  int mm = 0;
  int ss = 0;
  hh = glb_ptm->tm_hour;
  mm = glb_ptm->tm_min;
  ss = glb_ptm->tm_sec;

  int time[3] = {hh, mm, ss};
  int *timert = (int *)malloc(sizeof(int) * 3);
  memcpy(timert, time, sizeof(int) * 3);

  return timert;
}

int MinToMils(uint8_t Min)
{
  Min *= 60000;
  return Min;
}