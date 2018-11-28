// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#include "Arduino.h"
#include "../configuration.h"
#include "launch_control.h"
#include "light_manager.h"

LaunchControl::LaunchControl(LightManager *lightManager, Motor *needleMotor)
{
    this->lightManager = lightManager;
    this->needleMotor = needleMotor;
}

LaunchControl::~LaunchControl()
{
}

void LaunchControl::setPinModes()
{
    pinMode(PinOutConfiguration::MOTOR_STEP, OUTPUT);
    pinMode(PinOutConfiguration::MOTOR_DIR, OUTPUT);
    pinMode(PinOutConfiguration::MOTOR_RESET, OUTPUT);
    pinMode(PinOutConfiguration::BUZZER, OUTPUT);
    pinMode(PinOutConfiguration::BACKGROUND_LIGHT, OUTPUT);
    pinMode(PinOutConfiguration::NEEDLE_LIGHT, OUTPUT);
}

void LaunchControl::startBuzzerTest()
{
    digitalWrite(PinOutConfiguration::BUZZER, HIGH);
    delay(300);
    digitalWrite(PinOutConfiguration::BUZZER, LOW);
}

void LaunchControl::startLightTest()
{
    for (int i = 0; i <= 100; i++)
    {
        this->lightManager->setBrightness(LightManager::LightTypes::BackLight, i);
        this->lightManager->setBrightness(LightManager::LightTypes::NeedleLight, i);
        delay(Configuration::LIGHT_TEST_DELAY);
    }
    for (int i = 100; i >= 0; i--)
    {
        this->lightManager->setBrightness(LightManager::LightTypes::BackLight, i);
        this->lightManager->setBrightness(LightManager::LightTypes::NeedleLight, i);
        delay(Configuration::LIGHT_TEST_DELAY);
    }
    this->lightManager->setBrightness(LightManager::LightTypes::BackLight, Configuration::BACKGROUND_LIGHT_LEVEL);
    this->lightManager->setBrightness(LightManager::LightTypes::NeedleLight, Configuration::NEEDLE_LIGHT_LEVEL);
}

void LaunchControl::startMotor()
{
    this->needleMotor->resetToZero();
}

void LaunchControl::launch()
{
    this->setPinModes();
    this->startBuzzerTest();
    this->startLightTest();
    this->startMotor();
}
