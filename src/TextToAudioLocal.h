#pragma once
#include <Arduino.h>
#include "Constants.h"
#include "ITextToAudio.h"
#include <AudioTools.h>
#include "espeak.h"

using namespace audio_tools;

class TextToAudioLocal : public ITextToAudio
{
public:
    TextToAudioLocal();
    ~TextToAudioLocal() override;
    void Setup() override;
    void Play(const String& text) override;
    void Stop() override;
    void Teardown() override;
    void Tick() override;

private:
    I2SStream* i2s = nullptr;
    ESpeak* espeak = nullptr;
    bool speaking = false;
};
