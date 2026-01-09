#include "services.h"
#include "serv_blinky.h"
#include "serv_temperature_sensor.h"

void services_init(void)
{
    blinky_init();
    temperature_sensor_init();
}

void services_run(void)
{
    blinky_run();
    temperature_sensor_run();
}
