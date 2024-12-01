```
   _               _                 ___ _                             _______
  /_\  _ __   __ _| | ___   __ _    / _ \ |__   ___  _ __   ___      /` _____ `\;,
 //_\\| '_ \ / _` | |/ _ \ / _` |  / /_)/ '_ \ / _ \| '_ \ / _ \    /__(^===^)__\';,
/  _  \ | | | (_| | | (_) | (_| | / ___/| | | | (_) | | | |  __/      /  :::  \   ,;
\_/ \_/_| |_|\__,_|_|\___/ \__, | \/    |_| |_|\___/|_| |_|\___|     |   :::   | ,;'
                           |___/                                     '._______.'`
```
# Analog phone project

This project upgrades an old 1970s G.E.C. New Zealand Ltd POTS phone. The phone uses pulse dialing.

## Feature 1: Reminder system

If the receiver is on the hook (down), then you can dial number between 1 and 9. This will set a reminder for that number of minutes. When the time is up, the phone will ring 3 times.  The reminder ring can be stopped by lifting the receiver.

## Feature 2: Voice AI assistant

Not built yet. Initial thoughts...

If the recever is off the hook, then you can dial a number to activate the voice assistant. The number dialed will trigger actions:
- 1: Listen to a weather report
- 2: Listen to a joke
- 3: Speak to surfer dude
- 4: Speak to William Shakespeare

## Electronics

An ESP32-S3 has been added to read the dial pulses, read receiver hookup and control the ringer. The ESP32-S3 is powered by a USB 5 volt source. 

The microphone and speakers have been replaces and are connected to the ESP32-S3. Due to only 4 wires in cord, only an analog microphone can be used. The speaker is connected directly to a I2S DAC with an integrated 1w amplifier.

## Ringer circuit

The ringer electromagnet requires a voltage of 20 volts. The USB 5 volt source is boosted using a buck boost circuit from AliExpress. To recreate the the correct ring sound, the voltage is alternated via the L293D motor driver. There are two bells of different sizes, which creates an ocsillating sound.

Ring sequence:
- Ring for 400ms at 66Hz
- Pause for 200ms
- Ring for 400ms at 66Hz
- Pause for 1200ms
- Repeat