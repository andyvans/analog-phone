#pragma once
#include "Arduino.h"
#include "Constants.h"
#include "Dialer.h"
#include "Ringer.h"
#include "Reminder.h"

class Orchestrator
{
public:
    Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder);
    void Tick();

private:
    Dialer* dialer;
    Ringer* ringer;
    Reminder* reminder;
};