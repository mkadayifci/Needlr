// (c) 2018 Mehmet Kadayifci
// This code is licensed under MIT license (see the license file for details)

#ifndef configuration
#define configuration

namespace PinOutConfiguration
{

const int BACKGROUND_LIGHT = 3;
const int NEEDLE_LIGHT = 8;
const int BUZZER = 9;
const int MOTOR_STEP = 12;
const int MOTOR_DIR = 11;
const int MOTOR_RESET = 10;

} // namespace PinOutConfiguration
namespace Configuration
{
const int BACKGROUND_LIGHT_LEVEL = 50;
const int NEEDLE_LIGHT_LEVEL = 100;
const int LIGHT_TEST_DELAY = 10;
const int STEPS = 280 * 12; //315 * 12;
} // namespace Configuration
#endif
