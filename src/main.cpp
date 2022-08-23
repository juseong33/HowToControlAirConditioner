#include "Common.h"

unsigned long last = 0;
unsigned long now;
uint16_t WaterSensorVal;

void setup()
{
  Serial.begin(115200);
  Wifi_Init();
  InitIr();
  SendNecTest();
  delay(1000);
}

void loop()
{
  now = millis();
  //RecvLoop();
  WaterDetect();
  BackToRoutine();
  if (diff(now, last, 60000))
  {
    last = now;
    WaterSensorVal = analogRead(33U);
    if(WaterSensorVal <= 1000) WaterSensorVal = 0;
    int *glb_time_int_array = GetTimeForUserset();
    Serial.printf("%d시 : %d분 : %d초\n", glb_time_int_array[0], glb_time_int_array[1], glb_time_int_array[2]);
    Serial.printf("Water Sensor : %d\n", WaterSensorVal);

    if((glb_time_int_array[0] >= 9) && (glb_time_int_array[0] < 19) && (WaterSensorVal == 0))
    {
      DayTimeRoutine();
    }
    else if(((glb_time_int_array[0] >= 19) || ((glb_time_int_array[0] >= 0) && (glb_time_int_array[0] < 9))) && (WaterSensorVal == 0))
    {
      CheckMode();
      EveningRoutine();
    }
    /*  테스트를 위해 잠시 주석 처리
    if ((glb_time_int_array[2] >= 0) && (glb_time_int_array[2] < 30) && (WaterSensorVal == 0))
    { 
      DayTimeRoutine();
    }
    else if ((glb_time_int_array[2] >= 30) && (glb_time_int_array[2] < 60) && (WaterSensorVal == 0))
    {
      CheckMode();
      EveningRoutine(); 
    }
    */
  }
}