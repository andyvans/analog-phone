#include <Arduino.h>
#include "Ringer.h"

Ringer ringer;
void setup() 
{
  Serial.begin(115200);  
}

void loop() 
{  
  ringer.StartRinging();

  auto now = millis();
  while (millis() < now + 15000)
  {
    ringer.Ping();
  }
  
  ringer.StopRinging();  
}
