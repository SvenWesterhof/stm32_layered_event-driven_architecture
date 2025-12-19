
#include <pinout.h>
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "ips_display.h"
#include "ST7735/st7735.h"


HAL_StatusTypeDef ips_display_init() {
    ST7735_Init();
    ST7735_FillScreen(ST7735_RED);
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
    ST7735_FillScreen(ST7735_BLACK);

    // Prepare temperature string
    snprintf(temp_str, sizeof(temp_str), "Temp: %.2f C", temperature);
    // Prepare humidity string
    snprintf(hum_str, sizeof(hum_str), "Hum: %.2f %%", humidity);

    // Write temperature to display
    ST7735_WriteString(10, 30, temp_str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
    // Write humidity to display
    ST7735_WriteString(10, 60, hum_str, Font_11x18, ST7735_WHITE, ST7735_BLACK);

    return HAL_OK;
}

