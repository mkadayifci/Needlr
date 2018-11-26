#include "Arduino.h"
#include "../configuration.h"
#include "motor.h"

void Motor::step()
{
    digitalWrite(this->dirPin, this->currentDirection);
    digitalWrite(this->stepPin , HIGH);
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
