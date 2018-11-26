
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

LaunchControl *launchControl = new LaunchControl(lightManager,needleMotor);

int valueRange[2] = {0, 100};
int stepperRange[2] = {0, Configuration::STEPS};

long cycleTime = 1000000;




int currentStepDelay = 0;

int stepDelayInMicroseconds = 300;
int stepsRequired = 0;

void setup()
{
    Serial.begin(9600);

    launchControl->launch();

}

// int getTargetStep(long value)
// {
//     return map(value, valueRange[0], valueRange[1], stepperRange[0], stepperRange[1]);
// }
// void calculateAndSet(int targetValue)
// {
//     targetStep = getTargetStep(targetValue);
//     int stepDiff = targetStep - currentStep;
//     int stepDiffAbs = abs(stepDiff);
//     currentDirection = ((stepDiff)) < 0 ? Direction::CCW : Direction::CW;
//     currentStepDelay = (cycleTime - (stepDiffAbs * stepDelayInMicroseconds)) / stepDiffAbs;
// }


// void tick()
// {
//     if (currentStep != targetStep)
//     {
//         digitalWrite(PinOutConfiguration::MOTOR_DIR, currentDirection);
//         step();
//         currentStep = currentDirection == Direction::CW ? currentStep + 1 : currentStep - 1;

//         delayMicroseconds(currentStepDelay);
//     }
// }

void loop()
{
    if (Serial.available())
    {
        // int targetValue = Serial.read();
        // calculateAndSet(targetValue);
    }
    // tick();
}