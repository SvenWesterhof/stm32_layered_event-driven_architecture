#include "services.h"
#include "serv_blinky.h"
#include "serv_temperature_sensor.h"
#include "serv_display.h"
#include "serv_current_monitor.h"

void services_init(void)
{
    blinky_init();
    temperature_sensor_init();
    display_init();
    current_monitor_init();
}

void services_run(void)
{
    blinky_run();
    temperature_sensor_run();
    display_run();
    current_monitor_process();
}
