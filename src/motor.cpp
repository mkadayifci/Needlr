// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#include "Arduino.h"
#include "../configuration.h"
#include "motor.h"

void Motor::step()
{
    digitalWrite(this->dirPin, this->currentDirection);
    digitalWrite(this->stepPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(this->stepPin, LOW);
    delayMicroseconds(Motor::STEP_DELAY_MILISECONDS);
}

void Motor::resetToZero()
{
    digitalWrite(this->resetPin, HIGH);
    this->currentDirection = Motor::Direction::CCW;

    for (int i = 1; i < this->totalSteps; i++)
    {
        this->step();
    }
    this->currentStep = 0;
    this->currentDirection = Motor::Direction::CW;
}

void Motor::setPosition(int targetStep)
{

    this->targetStep = targetStep;
    int stepDiff = targetStep - currentStep;
    int stepDiffAbs = abs(stepDiff);
    currentDirection = ((stepDiff)) < 0 ? Direction::CCW : Direction::CW;
    this->calculatedExtraDelay = (this->cycleTime - (stepDiffAbs * Motor::STEP_DELAY_MILISECONDS)) / stepDiffAbs;

}


void Motor::tick()
{
    if (this->currentStep != this->targetStep)
    {
        this->step();
        this->currentStep = currentDirection == Direction::CW ? currentStep + 1 : currentStep - 1;
        delayMicroseconds( this->calculatedExtraDelay);
    }
}
