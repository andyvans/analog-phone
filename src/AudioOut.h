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
    void StartAnalogMic();
    void StartRadio();
    void Stop();
    void Tick();

private:
    //int sampleRate;
    AudioInfo* infoFrom;
    //AudioInfo infoTo;
    //SineWaveGenerator<int16_t> sineWave;
    //GeneratedSoundStream<int16_t> sound;
    //FormatConverterStream converter;

    URLStream* urlStream;
    ResampleStream* resampler;
    EncodedAudioStream* decodedStream;

    AudioStream* in;
    I2SStream* out;
    StreamCopy* copier;
};