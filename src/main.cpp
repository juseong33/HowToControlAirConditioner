#include "Common.h"

unsigned long long last = 0;
unsigned long long now;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    if(WiFi.status() == WL_CONNECTED)   Serial.println("WiFi Connected");
  }
  InitIr();
  delay(1000);
  SendNecTest();
}

void loop()
{
  now = millis();
  RecvLoop();
  if (diff(now, last, 3000))
  {
    last = now;
    int* glb_time_int_array = GetTimeForUserset();
    Serial.println("---------------------------------------");   
    Serial.printf("%d시 : %d분 : %d초 \n", glb_time_int_array[0], glb_time_int_array[1], glb_time_int_array[2]);
  }
}