#include "Orchestrator.h"

Orchestrator::Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder)
{
    this->dialer = dialer;
    this->ringer = ringer;
    this->reminder = reminder;
}

void Orchestrator::Tick()
{
    if (reminder->IsReminderTime())
    {
        Serial.println("Reminder time. Ringer started");
        reminder->Reset();
        ringer->StartRinging(3);
    }

    if (reminder->IsReminderTime() && !dialer->IsReceiverDown())
    {
        Serial.println("Reminder acknowledged. Ringer stopped");
        reminder->Reset();
        ringer->StopRinging();
    }

    // If the receiver is down and the dialer has dialed a number, then set a reminder
    if (dialer->HasDialedNumber() && dialer->IsReceiverDown())
    {
        auto dialedNumber = dialer->GetDialedNumber();
        dialer->Reset();

        if (dialedNumber > 0)
        {
            reminder->SetReminder(dialedNumber);
        }
        else
        {
            Serial.println("Cannot set reminder for 0 minutes");
        }
    }
}