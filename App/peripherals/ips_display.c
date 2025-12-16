
#include <pinout.h>
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "ips_display.h"
#include "ST7789/st7789.h"


HAL_StatusTypeDef ips_display_init() {
    ST7789_Init();
    return HAL_OK;
}

HAL_StatusTypeDef ips_display_open() {
    // Any additional setup can be done here
    return HAL_OK;
}

HAL_StatusTypeDef ips_display_close() {
    // Any cleanup can be done here
    return HAL_OK;
}

HAL_StatusTypeDef ips_display_write_temp_data(float temperature, float humidity) {
    char temp_str[20];
    char hum_str[20];

    // Clear the display
    ST7789_Fill_Color(BLACK);

    // Prepare temperature string
    snprintf(temp_str, sizeof(temp_str), "Temp: %.2f C", temperature);
    // Prepare humidity string
    snprintf(hum_str, sizeof(hum_str), "Hum: %.2f %%", humidity);

    // Write temperature to display
    ST7789_WriteString(10, 30, temp_str, Font_11x18, WHITE, BLACK);
    // Write humidity to display
    ST7789_WriteString(10, 60, hum_str, Font_11x18, WHITE, BLACK);

    return HAL_OK;
}

