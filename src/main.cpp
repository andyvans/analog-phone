// Analog phone project
//       _______
//     /` _____ `\;,
//    /__(^===^)__\';,
//      /  :::  \   ,;
//     |   :::   | ,;'
//     '._______.'`

#include <Arduino.h>
#include "Ringer.h"
#include "Dialer.h"

Ringer* ringer;
Dialer* dialer;

void setup()
{
  ringer = new Ringer();
  dialer = new Dialer();
  Serial.begin(115200);
}

void loop()
{
  dialer->Tick();
  if (dialer->HasDialedNumber())
  {
    auto dialedNumber = dialer->GetDialedNumber();
    Serial.println(dialedNumber);
    dialer->Reset();

    ringer->StartRinging(dialedNumber);
  }
}
