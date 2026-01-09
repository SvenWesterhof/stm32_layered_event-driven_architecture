#include "serv_blinky.h"
#include "main.h" // for externalLed_GPIO_Port and externalLed_Pin
#include "hal_gpio.h"
#include "hal_delay.h"

static uint32_t last_toggle = 0;
static uint32_t interval_ms = 2000;

void blinky_init(void)
{
    // Nothing to init for now, GPIO already initialized in MX_GPIO_Init
    last_toggle = hal_get_tick();
}

void blinky_run(void)
{
    uint32_t now = hal_get_tick();
    if ((now - last_toggle) >= interval_ms)
    {
        hal_gpio_toggle_pin((hal_gpio_port_t)externalLed_GPIO_Port, externalLed_Pin);
        last_toggle = now;
    }
}
