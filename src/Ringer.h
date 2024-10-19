#pragma once
#include "Arduino.h"
#include "Constants.h"

struct Sequence
{
  unsigned long endTime = 0;
  bool isBellOn = false;
};

class Ringer
{ 
public:
  Ringer();

  void Ping();
  void StartRinging();
  void StopRinging();

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
};
