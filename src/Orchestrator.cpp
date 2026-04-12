#include "Orchestrator.h"
#include "_Secrets.h"
#include <WiFi.h>

Orchestrator::Orchestrator(Dialer* dialer, Ringer* ringer, Reminder* reminder, ITextToAudio* textToAudio)
{
    this->dialer = dialer;
    this->ringer = ringer;
    this->reminder = reminder;
    this->textToAudio = textToAudio;
}

void Orchestrator::Setup()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to Wifi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }    
    
    Serial.println("Wifi connected. IP: " + WiFi.localIP().toString());
    ringer->RingBell(1);
    textToAudio->Play("The system is online. Please set a reminder by dialing a number and picking up the receiver. Dialing 0 will set a reminder for 5 seconds, while dialing any other number will set a reminder for that many minutes.");
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