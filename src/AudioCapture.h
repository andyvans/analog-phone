#pragma once
#include <Arduino.h>
#include "Constants.h"
#include <AudioTools.h>
#include <AudioTools/Communication/AudioHttp.h>

using namespace audio_tools;

class AudioCapture
{
public:
    AudioCapture();
    void Setup();
    void Start();
    void Stop();
    void Tick();

private:
    AudioInfo* infoFrom;
    
    URLStream* urlStream;
    ResampleStream* resampler;
    EncodedAudioStream* decodedStream;

    AudioStream* in;
    I2SStream* out;
    StreamCopy* copier;
};