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
    }
}

void Reminder::SetReminder(int reminderMinutes)
{
    Serial.print("Reminder in minutes: ");
    Serial.println(reminderMinutes);
    reminderTime = millis() + (reminderMinutes * 60 * 1000);
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
}