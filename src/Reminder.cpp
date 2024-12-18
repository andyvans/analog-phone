#include "Reminder.h"
#include "Dialer.h"
#include "Ringer.h"

Reminder::Reminder()
{
}

void Reminder::Tick()
{
    if (isReminderSet && millis() > reminderTime)
    {
        isReminderTime = true;
        isReminderSet = false;
        reminderStartTime = millis();
    }
}

void Reminder::SetReminder(unsigned long reminderSeconds)
{
    Serial.print("Reminder in seconds: ");
    Serial.println(reminderSeconds);
    reminderTime = millis() + (reminderSeconds * 1000);
    isReminderSet = true;
}

bool Reminder::IsReminderSet()
{
    return isReminderSet;
}

bool Reminder::IsReminderTime()
{
    return isReminderTime;
}

void Reminder::Reset()
{
    Serial.println("Reminder reset");
    isReminderTime = false;
    isReminderSet = false;
    reminderTime = 0;
    reminderStartTime = 0;
    isAlerting = false;
}

void Reminder::StartAlert()
{
    Serial.println("Reminder alert started");
    isAlerting = true;
    alertStartTime = millis();
}

bool Reminder::IsAlerting()
{
    return isAlerting;
}

bool Reminder::IsAlertExpired()
{
    return isAlerting && alertStartTime + 10000 < millis();
}