#pragma once
#include "Arduino.h"
#include "Constants.h"

class Dialer
{
public:
    Dialer();

    void Tick();
    bool IsDialing();
    bool HasDialedNumber();
    int GetDialedNumber();
    void Reset();

private:
    bool isDialing = false;
    bool isAwaitingDigit = false;
    int digitStartTime = 0;
    bool hasDialedNumber = false;
    unsigned long lastDialTime = 0;
    int dialerCount = 0;
};