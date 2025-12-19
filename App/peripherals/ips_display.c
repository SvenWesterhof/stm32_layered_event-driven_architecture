
#include <pinout.h>
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "ips_display.h"
#include "ST7735/st7735.h"


HAL_StatusTypeDef ips_display_init() {
    ST7735_Init();
    // Fill background
    ST7735_FillScreen(ST7735_BLACK);

    // Draw static labels
    ST7735_WriteString(10, 10, "Temp: ", Font_11x18, ST7735_WHITE, ST7735_BLACK);
    ST7735_WriteString(10, 40, "Hum:  ", Font_11x18, ST7735_WHITE, ST7735_BLACK);

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
    char temp_val[10];
    char hum_val[10];

    // Format the numeric values only
    int temp_int = (int)temperature;
    int temp_frac = (int)((temperature - temp_int) * 100);
    snprintf(temp_val, sizeof(temp_val), "%d.%02d C", temp_int, temp_frac);

    int hum_int = (int)humidity;
    int hum_frac = (int)((humidity - hum_int) * 100);
    snprintf(hum_val, sizeof(hum_val), "%d.%02d %%", hum_int, hum_frac);

    // Overwrite only the numeric values on the display
    ST7735_WriteString(80, 10, temp_val, Font_11x18, ST7735_WHITE, ST7735_BLACK);
    ST7735_WriteString(80, 40, hum_val, Font_11x18, ST7735_WHITE, ST7735_BLACK);

    return HAL_OK;
}
