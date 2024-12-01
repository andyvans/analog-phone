#pragma once
#include "Arduino.h"
#include "Constants.h"

class Reminder
{
public:
    Reminder();
    void Tick();
    void SetReminder(unsigned long reminderSeconds);
    bool IsReminderSet();
    bool IsReminderTime();
    void Reset();

private:
    unsigned long reminderTime = 0;
    unsigned long reminderStartTime = 0;
    bool isReminderTime = false;
    bool isReminderSet = false;
};