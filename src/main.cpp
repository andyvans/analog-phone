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
#include "TextToAudioAzure.h"

Ringer* ringer;
Dialer* dialer;
Reminder* reminder;
Orchestrator* orchestrator;
AudioCapture* audioCapture;
ITextToAudio* textToAudio;

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

  textToAudio = new TextToAudioAzure();
  textToAudio->Setup();

  //audioCapture = new AudioCapture();
  //audioCapture->Setup();
  //audioCapture->Start();
  
  orchestrator = new Orchestrator(dialer, ringer, reminder, textToAudio);

  xTaskCreatePinnedToCore(ProcessAudio, "Audio", 10000, NULL, 1, &AudioTask, 1);
  xTaskCreatePinnedToCore(ProcessDevices, "Device", 10000, NULL, 1, &DeviceTask, 1);

  delay(100);
  orchestrator->Setup();
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