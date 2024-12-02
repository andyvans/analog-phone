#pragma once
#include "Arduino.h"
#include "Constants.h"

struct Sequence
{
  unsigned long endTime = 0;
  bool isBellOn = false;
};

// This class manages the ringer
class Ringer
{
public:
  Ringer();

  void Tick();
  void StartRinging();
  void StopRinging();
  bool IsRinging();
  void RingBell(int count);

private:
  void RestartSequence();
  void StopBell();
  void Ring();
  void Bell();

  bool isRinging = false;  
  int sequence = 0;
  Sequence sequences[4];
  int bellPosition = 0;
  unsigned long lastBellTime = 0;

  bool isAlerting = false;
  unsigned long lastAlertTime = 0;  
};
