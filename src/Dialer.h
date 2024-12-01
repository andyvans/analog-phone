#pragma once
#include "Arduino.h"
#include "Constants.h"

// This class manages the pulse dialler and the receiver hook switch
class Dialer
{
public:
    Dialer();

    void Tick();
    bool IsDialing();
    bool HasDialedNumber();
    int GetDialedNumber();
    void Reset();
    bool IsReceiverDown();

private:
    void SetDialedNumber(int number);
    bool isReceiverDown = false;
    int receiverChangeTime = 0;
    int dialedNumber = -1;
    bool isDialing = false;
    bool isAwaitingDigit = false;
    int digitStartTime = 0;
    unsigned long lastDialTime = 0;
    int pulseCount = 0;
};