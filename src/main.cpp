#include "Common.h"

unsigned long long last = 0;
unsigned long long now;
uint16_t WaterSensorVal;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    if (WiFi.status() == WL_CONNECTED)  Serial.println("WiFi Connected"); 
  }
  InitIr();
  SendNecTest();
  delay(1000);
}

void loop()
{
  now = millis();
  RecvLoop();
  WaterDetect();
  if (diff(now, last, 10000) && (WaterSensorVal == 0))
  {
    last = now;
    int *glb_time_int_array = GetTimeForUserset();
    WaterSensorVal = analogRead(33U);
    Serial.printf("%d시 : %d분 : %d초\n", glb_time_int_array[0], glb_time_int_array[1], glb_time_int_array[2]);
    Serial.printf("Water Sensor : %d\n", WaterSensorVal);
    /*   테스트를 위해 잠시 주석 처리
    if((glb_time_int_array[0] >= 9) && (glb_time_int_array[0] < 19))
    {
      DayTimeRoutine();
    }
    else if((glb_time_int_array[0] >= 19) || ((glb_time_int_array[0] >= 0) && (glb_time_int_array[0] < 9)))
    {
      CheckMode();
      EveningRoutine();
    }
    */
    if ((glb_time_int_array[2] >= 0) && (glb_time_int_array[2] <= 30))
    {
      DayTimeRoutine();
    }
    else
    {
      CheckMode();
      EveningRoutine();
    }
  }
}