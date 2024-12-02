#include "Ringer.h"

Ringer::Ringer()
{
    pinMode(H_BRIDGE_PIN1, OUTPUT);
    pinMode(H_BRIDGE_PIN2, OUTPUT);
}

void Ringer::StartRinging()
{
    Serial.println("Start ringing");
    isRinging = true;
    RestartSequence();
}

void Ringer::StopRinging()
{
    Serial.println("Stop ringing");
    StopBell();
    isRinging = false;
}

void Ringer::RingBell(int count)
{
    count = max(count, 1);
    Serial.print("Ring bell: ");
    Serial.println(count);
    lastAlertTime = millis() + (count * 50);
    isAlerting = true;
}

bool Ringer::IsRinging()
{
    return isRinging;
}

void Ringer::Tick()
{
    // Expire the alert
    if (isAlerting && millis() > lastAlertTime)
    {
        isAlerting = false;
    }

    if (isRinging || isAlerting)
    {
        Ring();
    }
}

// This is the sequence of the bell ringing and is a close approximation of the sound of NZ 1980s POTS bell ringing
void Ringer::RestartSequence()
{
    sequence = 0;
    sequences[0].isBellOn = true;
    sequences[0].endTime = millis() + 400;

    sequences[1].isBellOn = false;
    sequences[1].endTime = sequences[0].endTime + 200;

    sequences[2].isBellOn = true;
    sequences[2].endTime = sequences[1].endTime + 400;

    sequences[3].isBellOn = false;
    sequences[3].endTime = sequences[2].endTime + 1200;
}

void Ringer::Ring()
{
    //Serial.println("Ring");
    unsigned long currentMillis = millis();
    auto currentSequence = sequences[sequence];
    if (currentMillis < currentSequence.endTime)
    {
        if (currentSequence.isBellOn)
        {
            Bell();
        }
        else
        {
            StopBell();
        }
    }
    else
    {
        sequence++;
        if (sequence == 4)
        {
            RestartSequence();
        }
    }
}

void Ringer::StopBell()
{
    //Serial.println("Stop bell");
    digitalWrite(H_BRIDGE_PIN1, LOW);
    digitalWrite(H_BRIDGE_PIN2, LOW);
}

void Ringer::Bell()
{
    //Serial.println("Bell");
    unsigned long currentMillis = millis();
    if (currentMillis - lastBellTime >= 15)
    {
        lastBellTime = currentMillis;
        if (bellPosition == 0)
        {
            // Left bell
            digitalWrite(H_BRIDGE_PIN1, HIGH);
            digitalWrite(H_BRIDGE_PIN2, LOW);
            bellPosition = 1;
        }
        else
        {
            // Right bell
            digitalWrite(H_BRIDGE_PIN1, LOW);
            digitalWrite(H_BRIDGE_PIN2, HIGH);
            bellPosition = 0;
        }
    }
}
