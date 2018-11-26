#include "Arduino.h"
#include "light_manager.h"
#include "motor.h"
#ifndef launch_control
#define launch_control

class LaunchControl
{
    LightManager *lightManager;
    Motor *needleMotor;

  private:
    void startLightTest();
    void startBuzzerTest();
    void startMotor();
  public:
    LaunchControl(LightManager *lightManager,Motor *needleMotor)
    {
        this->lightManager = lightManager;   
        this->needleMotor = needleMotor;
    };
    ~LaunchControl(){};
    void setPinModes();
    void launch();

};

#endif