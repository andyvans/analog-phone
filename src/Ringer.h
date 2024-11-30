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

  void Tick();
  void StartRinging(int ringCount);
  void StopRinging();

private:
  void RestartSequence();
  void StopBell();
  void Ring();
  void Bell();

  int ringCount = 0;
  bool isRinging = false;
  int sequence = 0;
  Sequence sequences[4];
  int bellPosition = 0;
  unsigned long lastBellTime = 0;
};
