#include "Orchestrator.h"

Orchestrator::Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder)
{
    this->dialer = dialer;
    this->ringer = ringer;
    this->reminder = reminder;
}

void Orchestrator::Tick()
{
    if (reminder->IsReminderTime() && !ringer->IsRinging())
    {
        Serial.println("Reminder time. Ringer started");
        ringer->StartRinging(3);
    }

    if (reminder->IsReminderTime() && ringer->IsRinging() && !dialer->IsReceiverDown())
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

        // If the dialed number is 0, then set a reminder for 30 seconds, else minutes
        auto reminderSeconds = dialedNumber == 0 ? 30 : dialedNumber * 60;
        reminder->SetReminder(reminderSeconds);
    }
}