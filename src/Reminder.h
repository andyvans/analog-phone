#pragma once
#include "Arduino.h"
#include "Constants.h"

class Reminder
{
public:
    Reminder();
    void Tick();
    void SetReminder(int reminderMinutes);
    bool IsReminderSet();
    bool IsReminderTime();
    void Reset();

private:
    unsigned long reminderTime = 0;
    bool isReminderTime = false;
    bool isReminderSet = false;
};