#pragma once
#include <Arduino.h>
#include "Constants.h"
#include <AudioTools.h>

using namespace audio_tools;

class AudioOut
{
public:
    AudioOut();
    void Setup();
    void Tick();

private:
    AudioInfo info;
    SineWaveGenerator<int16_t> sineWave;
    GeneratedSoundStream<int16_t> sound;
    I2SStream out;
    StreamCopy copier;
};