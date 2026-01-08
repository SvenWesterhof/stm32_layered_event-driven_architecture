#include "feat_blinky.h"
#include "main.h" // for externalLed_GPIO_Port and externalLed_Pin
#include "stm32f7xx_hal.h"

static uint32_t last_toggle = 0;
static uint32_t interval_ms = 2000;

void blinky_init(void)
{
    // Nothing to init for now, GPIO already initialized in MX_GPIO_Init
    last_toggle = HAL_GetTick();
}

void blinky_run(void)
{
    uint32_t now = HAL_GetTick();
    if ((now - last_toggle) >= interval_ms)
    {
        HAL_GPIO_TogglePin(externalLed_GPIO_Port, externalLed_Pin);
        last_toggle = now;
    }
}
