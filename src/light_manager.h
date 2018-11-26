#include "Arduino.h"
#ifndef light_manager
#define light_manager

class LightManager
{

  public:
    enum LightTypes
    {
        BackLight,
        NeedleLight
    };

  private:
    int getPinNumberByLightType(LightManager::LightTypes type);

  public:
    LightManager(){};
    ~LightManager(){};
    void setBrightness(LightManager::LightTypes type, int value);
};

#endif