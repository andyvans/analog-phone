#include "Orchestrator.h"

Orchestrator::Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder)
{
    this->dialer = dialer;
    this->ringer = ringer;
    this->reminder = reminder;
}

void Orchestrator::Tick()
{
    // Start the ringer if the reminder time has been reached
    if (reminder->IsReminderTime() && !reminder->IsAlerting())
    {
        Serial.println("Reminder time. Ringer started");
        reminder->StartAlert();
        ringer->StartRinging();
    }

    // Stop the ringer if the receiver is picked up or the alert has expired  
    if ((!dialer->IsReceiverDown() && reminder->IsAlerting()) || reminder->IsAlertExpired())
    {
        if (reminder->IsAlertExpired())
        {
            Serial.println("Reminder expired");
        }
        else
        {
            Serial.println("Receiver picked up");
        }
        ringer->StopRinging();
        reminder->Reset();
    }

    // If the receiver is down and the dialer has dialed a number, then set a reminder
    if (dialer->HasDialedNumber() && dialer->IsReceiverDown())
    {
        auto dialedNumber = dialer->GetDialedNumber();
        dialer->Reset();

        // If the dialed number is 0, then set a reminder for 30 seconds, else minutes
        auto reminderSeconds = dialedNumber == 0 ? 5 : dialedNumber * 60;
        reminder->SetReminder(reminderSeconds);
        ringer->RingBell(1);
    }
}