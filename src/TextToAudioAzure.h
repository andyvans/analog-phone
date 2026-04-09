#pragma once
#include <Arduino.h>
#include "Constants.h"
#include "ITextToAudio.h"
#include <AudioTools.h>
#include <AudioTools/Communication/AudioHttp.h>

using namespace audio_tools;

class TextToAudioAzure : public ITextToAudio
{
public:
    TextToAudioAzure();
    ~TextToAudioAzure() override;
    void Setup() override;
    void Play(const String& text) override;
    void Stop() override;
    void Teardown() override;
    void Tick() override;

private:
    URLStream* urlStream = nullptr;
    I2SStream* i2s = nullptr;
    StreamCopy* copier = nullptr;
};