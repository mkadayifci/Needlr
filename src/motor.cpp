// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#include "Arduino.h"
#include "../configuration.h"
#include "motor.h"

Motor::Motor(int dirPin, int resetPin, int stepPin, int totalSteps)
{
    this->dirPin = dirPin;
    this->resetPin = resetPin;
    this->stepPin = stepPin;
    this->totalSteps = totalSteps;
}

Motor::~Motor()
{
}

bool Motor::step()
{
    long realTimeReferenceValue = micros();
    long realTimeWallClockTime = 0;
    long estimatedTime = 0;
    this->freeToMoveCalculation();

    if (this->freeToMove)
    {
        digitalWrite(this->stepPin, HIGH);
        delayMicroseconds(5);
        digitalWrite(this->stepPin, LOW);
        this->freeToMove = false;
        realTimeWallClockTime = micros() - realTimeReferenceValue;
        this->timeCorrection = realTimeWallClockTime;
        this->lastMicro = micros();
        return true;
    }
    return false;
}

void Motor::resetToZero()
{
    digitalWrite(this->resetPin, HIGH);
    this->setDirection(Motor::Direction::CCW);
    int zeroStepCounter = 0;
    while (zeroStepCounter < this->totalSteps)
    {
        if (this->step())
        {
            zeroStepCounter++;
        }
    }
    this->currentStep = 0;
    this->setDirection(Motor::Direction::CW);
}

void Motor::setDirection(Motor::Direction direction)
{
    this->currentDirection = direction;
    digitalWrite(this->dirPin, this->currentDirection);
}

void Motor::setPosition(int targetStep)
{
    this->targetStep = targetStep;
    this->startStep = this->currentStep;
    int stepDiff = targetStep - currentStep;
    int stepDiffAbs = abs(stepDiff);
    this->setDirection(((stepDiff)) < 0 ? Direction::CCW : Direction::CW);
    long cycleTimeAfterEdgeDelay = this->cycleTime - (Motor::EDGE_EXTRA_DELAY * Motor::EDGE_SENSOR_VALUE * 2);
    this->calculatedExtraDelay = (cycleTimeAfterEdgeDelay - (stepDiffAbs * Motor::STEP_DELAY_MICROSECONDS)) / stepDiffAbs;
}

void Motor::tick()
{
    if (this->currentStep != this->targetStep)
    {
        if (this->step())
        {
            this->currentStep = currentDirection == Direction::CW ? currentStep + 1 : currentStep - 1;
        }
    }
}

bool Motor::isCloseToEdges()
{
    if (this->targetStep == 0)
    {
        return false;
    }
    return (abs(this->currentStep - this->targetStep) < Motor::EDGE_SENSOR_VALUE) ||
           (abs(this->startStep - this->currentStep) < Motor::EDGE_SENSOR_VALUE);
}

long Motor::freeToMoveCalculation()
{
    long totalDelay = Motor::STEP_DELAY_MICROSECONDS + this->calculatedExtraDelay;
    if (this->isCloseToEdges())
    {
        totalDelay += Motor::EDGE_EXTRA_DELAY;
    }
    if ((micros() - this->lastMicro) >= (totalDelay - this->timeCorrection))
    {

        this->freeToMove = true;
    }
}