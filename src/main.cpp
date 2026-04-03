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
#include "AudioCapture.h"
#include "TextToAudio.h"

Ringer* ringer;
Dialer* dialer;
Reminder* reminder;
Orchestrator* orchestrator;
AudioCapture* audioCapture;
TextToAudio* textToAudio;

TaskHandle_t DeviceTask;
TaskHandle_t AudioTask;

void ProcessDevices(void* parameter);
void ProcessAudio(void* parameter);

void setup()
{
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);
  
  ringer = new Ringer();
  dialer = new Dialer();
  reminder = new Reminder();

  textToAudio = new TextToAudio();
  textToAudio->Setup();

  orchestrator = new Orchestrator(dialer, ringer, reminder, textToAudio);

  //audioCapture = new AudioCapture();
  //audioCapture->Setup();
  //audioCapture->Start();

  xTaskCreatePinnedToCore(ProcessAudio, "Audio", 10000, NULL, 1, &AudioTask, 0);
  xTaskCreatePinnedToCore(ProcessDevices, "Device", 10000, NULL, 1, &DeviceTask, 1);
}

void loop()
{
  // All processing is done in the tasks  
}

void ProcessDevices(void* parameter)
{
  for (;;)
  {
    dialer->Tick();
    ringer->Tick();
    reminder->Tick();
    orchestrator->Tick();
    vTaskDelay(1);
  }
}

void ProcessAudio(void* parameter)
{
  for (;;)
  {
    audioCapture->Tick();
    textToAudio->Tick();
    vTaskDelay(1);
  }
}