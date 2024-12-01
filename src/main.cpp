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
#include "Reminder.h"
#include "Orchestrator.h"

Ringer* ringer;
Dialer* dialer;
Reminder* reminder;
Orchestrator* orchestrator;

void setup()
{
  Serial.begin(115200);
  ringer = new Ringer();
  dialer = new Dialer();
  reminder = new Reminder();
  orchestrator = new Orchestrator(dialer, ringer, reminder);
}

void loop()
{
  dialer->Tick();
  ringer->Tick();
  reminder->Tick();
  orchestrator->Tick();
}