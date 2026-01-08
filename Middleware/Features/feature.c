#include "feature.h"
#include "feat_blinky.h"
#include "feat_temperature_sensor.h"

void feature_init(void)
{
    blinky_init();
    temperature_sensor_init();
}

void feature_run(void)
{
    blinky_run();
    temperature_sensor_run();
}
