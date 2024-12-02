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

TaskHandle_t AudioTask;
TaskHandle_t DeviceTask;

void ProcessDevices(void* parameter);
void ProcessAudio(void* parameter);

void setup()
{
  Serial.begin(115200);
  ringer = new Ringer();
  dialer = new Dialer();
  reminder = new Reminder();
  orchestrator = new Orchestrator(dialer, ringer, reminder);

  xTaskCreatePinnedToCore(ProcessDevices, "Devices", 10000, NULL, 1, &DeviceTask, 0);
  xTaskCreatePinnedToCore(ProcessAudio, "Audio", 10000, NULL, 1, &AudioTask, 1);
}

void loop()
{
  // All processing is done in the tasks  
}

void ProcessDevices(void* parameter)
{
  dialer->Tick();
  ringer->Tick();
  reminder->Tick();
  orchestrator->Tick();
}

void ProcessAudio(void* parameter)
{

}