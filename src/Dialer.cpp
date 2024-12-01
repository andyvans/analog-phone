#include "Dialer.h"

Dialer::Dialer()
{
    pinMode(DIALER_PIN1, INPUT_PULLUP);
    pinMode(DIALER_PIN2, INPUT_PULLUP);
    pinMode(RECEIVER_PIN, INPUT_PULLUP);
}

void Dialer::Reset()
{
    isDialing = false;
    lastDialTime = 0;
    dialerCount = 0;
    dialedNumber = -1;
}

bool Dialer::IsDialing()
{
    return isDialing;
}

bool Dialer::HasDialedNumber()
{
    return dialedNumber >= 0;
}

void Dialer::SetDialedNumber(int number)
{
    Serial.print("Number dialed:");
    Serial.println(number);
    dialerCount = 0;
    dialedNumber = number;
}

int Dialer::GetDialedNumber()
{
    auto newDialedNumber = dialedNumber;
    dialedNumber = -1;
    return newDialedNumber;
}

bool Dialer::IsReceiverDown()
{
    return isReceiverDown;
}

// Count the number of dialer pulses
void Dialer::Tick()
{
    // Check if the receiver is down
    auto newIsReceiverDown = digitalRead(RECEIVER_PIN) == HIGH;
    auto newReceiverChangeTime = millis();
    auto allowChange = (newReceiverChangeTime - receiverChangeTime) > 200;
    if (!isReceiverDown && newIsReceiverDown && allowChange)
    {
        Serial.println("Receiver down");
        Reset();
        receiverChangeTime = newReceiverChangeTime;
    }
    else if (isReceiverDown && !newIsReceiverDown && allowChange)
    {
        Serial.println("Receiver up");
        Reset();
        receiverChangeTime = newReceiverChangeTime;
    }
    isReceiverDown = newIsReceiverDown;

    // Check if the dialer is dialing
    auto newIsDialing = digitalRead(DIALER_PIN1) == LOW;
    if (!newIsDialing && isDialing)
    {
        //Serial.println("end");
        isDialing = false;
        lastDialTime = millis();

        // NZ phones are 0-9, so 10 pulses are allowed
        if (dialerCount > 0 && dialerCount <= 10)
        {
            SetDialedNumber(10 - dialerCount);
        }
        else if (dialerCount > 10)
        {
            Serial.print("Invalid digits dialed: ");
            Serial.println(dialerCount);
        }
    }
    else if (newIsDialing && !isDialing)
    {
        //Serial.println("start");
        isDialing = true;
        isAwaitingDigit = true;
    }

    if (!isDialing)
    {
        return;
    }

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
