// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#include "configuration.h"
#include "src/light_manager.h"
#include "src/launch_control.h"
#include "src/motor.h"

LightManager *lightManager = new LightManager();

Motor *needleMotor = new Motor(
    PinOutConfiguration::MOTOR_DIR,
    PinOutConfiguration::MOTOR_RESET,
    PinOutConfiguration::MOTOR_STEP,
    Configuration::STEPS);

LaunchControl *launchControl = new LaunchControl(lightManager, needleMotor);

long cycleTime = 1000000;

int currentStepDelay = 0;

int stepDelayInMicroseconds = 300;
int stepsRequired = 0;

void setup()
{
    Serial.begin(9600);

    launchControl->launch();
}


void loop()
{
    if (Serial.available())
    {
        int value = Serial.read();
        needleMotor->setPosition(map(value, 0, 100, 1, Configuration::STEPS));
    }
    needleMotor->tick();
}