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
    int dirPin;
    int resetPin;
    int stepPin;
    int totalSteps;

    int currentStep = 0;
    int targetStep = 0;
    Motor::Direction currentDirection = Motor::Direction::CW;

    const int STEP_DELAY_MILISECONDS = 300;

private:
    void step();
  public:
    void moveToPosition(int position);
    void resetToZero();
    Motor(int dirPin, int resetPin, int stepPin, int totalSteps)
    {
        this->dirPin = dirPin;
        this->resetPin = resetPin;
        this->stepPin = stepPin;
        this->totalSteps = totalSteps;
    };
    ~Motor(){};
};

#endif