#include "Arduino.h"
#include "../configuration.h"
#include "light_manager.h"

void LightManager::setBrightness(LightManager::LightTypes type, int value)
{
    long mappedValue = map(value, 0, 100, 0, 255);
    int targetPinNumber = this->getPinNumberByLightType(type);
    analogWrite(targetPinNumber, mappedValue);
}

int LightManager::getPinNumberByLightType(LightManager::LightTypes type)
{
    switch (type)
    {
    case LightManager::LightTypes::BackLight:
        return PinOutConfiguration::BACKGROUND_LIGHT;
    case LightManager::LightTypes::NeedleLight:
        return PinOutConfiguration::NEEDLE_LIGHT;
    default:
        return 0;
    }
}

