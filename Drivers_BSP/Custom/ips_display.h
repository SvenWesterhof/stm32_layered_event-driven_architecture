#ifndef IPS_DISPLAY_H
#define IPS_DISPLAY_H

#include "stm32f7xx_hal.h"

HAL_StatusTypeDef ips_display_init();
HAL_StatusTypeDef ips_display_open();
HAL_StatusTypeDef ips_display_close();

HAL_StatusTypeDef ips_display_write_temp_data(float temperature, float humidity);


#endif // IPS_DISPLAY_H
