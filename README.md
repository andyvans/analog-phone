```
       _______
     /` _____ `\;,
    /__(^===^)__\';,
      /  :::  \   ,;
     |   :::   | ,;'
     '._______.'`

```
# Analog phone project

This was a phone in my house a when I was a kid. The phone uses pulse dialing and was configured for the POTS in New Zealand.

## Part 1: Reminder system

If the receiver is down, then you can dial number between 1 and 9. This will set a reminder for that number of minutes. When the time is up, the phone will ring 3 times.

## Part 2: Voice AI assistant

to be continued...

## Ringer circuit

The ringer requires a voltage of 20 volts. The USB 5 volt source is boosted using a buck boost circuit. To recreate the the correct ring sound, the voltage is alternated via the L293D motor driver. The delays are in `Ringer.cpp`. Note that there are two bells of different sizes. The two bell tones creates an ocsillating sound.

Ring sequence:
- Ring for 400ms at 66Hz
- Pause for 200ms
- Ring for 400ms at 66Hz
- Pause for 1200ms
- Repeat