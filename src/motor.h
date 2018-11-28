// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#include "Arduino.h"
#ifndef motor
#define motor

class Motor
{

public:
  enum LightTypes
  {
    BackLight,
    NeedleLight
  };

  enum Direction
  {
    CW = 0,
    CCW = 1
  };

private:
  const int STEP_DELAY_MICROSECONDS = 300;
  const int EDGE_SENSOR_VALUE = 30;
  const int EDGE_EXTRA_DELAY = 1000;
  int dirPin;
  int resetPin;
  int stepPin;
  int totalSteps;
  long lastMicro = 0;
  bool freeToMove = true;
  long timeCorrection = 0;
  int currentStep = 0;
  int startStep = 0;
  int targetStep = 0;
  int calculatedExtraDelay = 0;
  long cycleTime = 1000000;
  Motor::Direction currentDirection = Motor::Direction::CW;

private:
  bool step();
  long freeToMoveCalculation();
  bool isCloseToEdges();
  void setDirection(Motor::Direction direction);

public:
  void setPosition(int position);
  void resetToZero();
  void tick();
  Motor(int dirPin, int resetPin, int stepPin, int totalSteps);
  ~Motor();
};

#endif