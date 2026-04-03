#pragma once
#include <Arduino.h>
#include "Constants.h"
#include <AudioTools.h>
#include <AudioTools/Communication/AudioHttp.h>

using namespace audio_tools;

class TextToAudio
{
public:
    TextToAudio();
    ~TextToAudio();
    void Setup();
    void Play(const String& text);
    void Stop();
    void Teardown();
    void Tick();

private:
    URLStream* urlStream = nullptr;
    I2SStream* i2s = nullptr;
    StreamCopy* copier = nullptr;
};