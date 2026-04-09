#pragma once
#include <Arduino.h>

class ITextToAudio
{
public:
    virtual ~ITextToAudio() = default;
    virtual void Setup() = 0;
    virtual void Play(const String& text) = 0;
    virtual void Stop() = 0;
    virtual void Teardown() = 0;
    virtual void Tick() = 0;
};
