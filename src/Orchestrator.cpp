#include "Orchestrator.h"

Orchestrator::Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder, TextToAudio* textToAudio)
{
    this->dialer = dialer;
    this->ringer = ringer;
    this->reminder = reminder;
    this->textToAudio = textToAudio;

    textToAudio->Play("The system is online");
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
        if (reminder->IsAlertExpired()) Serial.println("Reminder expired");
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

    if (dialer->HasDialedNumber() && !dialer->IsReceiverDown())
    {
        auto dialedNumber = dialer->GetDialedNumber();
        dialer->Reset();

        // If the dialed number is 0, then play a test message, else play the number
        if (dialedNumber == 0)
        {
            textToAudio->Play("This is a test message. The system is working correctly.");
        }
        else
        {
            textToAudio->Play("You have dialed " + String(dialedNumber));
        }
    }
}