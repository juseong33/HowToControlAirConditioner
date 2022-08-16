#include "Common.h"

void setup()
{
  Serial.begin(115200);
  RecvSet();      // IR 수신
}

void loop()
{
  RecvLoop();     // IR 수신
}