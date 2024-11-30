#include "Dialer.h"

Dialer::Dialer()
{
    pinMode(DIALER_PIN1, INPUT_PULLUP);
    pinMode(DIALER_PIN2, INPUT_PULLUP);
}

void Dialer::Reset()
{
    isDialing = false;
    hasDialedNumber = false;
    lastDialTime = 0;
    dialerCount = 0;
}

bool Dialer::IsDialing()
{
    return isDialing;
}

bool Dialer::HasDialedNumber()
{
    return hasDialedNumber;
}

// Returns the dialed number and resets the dialer
int Dialer::GetDialedNumber()
{
    // NZ phone dialers are 0-9
    auto dialedNumber = 10 - dialerCount;
    dialerCount = 0;
    return dialedNumber;
}

// Count the number of dialer pulses
void Dialer::Tick()
{
    auto newIsDialing = digitalRead(DIALER_PIN1) == LOW;

    if (!newIsDialing && isDialing)
    {
        //Serial.println("end");
        isDialing = false;
        hasDialedNumber = dialerCount > 0;
        lastDialTime = millis();
        return;
    }
    else if (newIsDialing && !isDialing)
    {
        //Serial.println("start");
        isDialing = true;
        isAwaitingDigit = true;
        return;
    }

    if (!isDialing) return;

    if (isAwaitingDigit)
    {
        //Serial.println("reading digit");
        auto digitRelease = digitalRead(DIALER_PIN2) == HIGH;
        if (digitRelease && (millis() - digitStartTime) > 40)
        {
            dialerCount++;
            isAwaitingDigit = false;
            //Serial.print("digit ++");
        }
    }
    else
    {
        auto digitStart = digitalRead(DIALER_PIN2) == LOW;
        if (digitStart)
        {
            digitStartTime = millis();
            isAwaitingDigit = true;
            //Serial.println("awaiting digit");
        }
    }
}
