
#include <pinout.h>
#include <stdio.h>
#include "ips_display.h"
#include "st7735.h"


ips_display_status_t ips_display_init() {
    ST7735_Init();
    // Fill background
    ST7735_FillScreen(ST7735_BLACK);

    // Draw static labels
    ST7735_WriteString(10, 10, "Temp: ", Font_11x18, ST7735_WHITE, ST7735_BLACK);
    ST7735_WriteString(10, 40, "Hum:  ", Font_11x18, ST7735_WHITE, ST7735_BLACK);

    return IPS_DISPLAY_OK;
}

ips_display_status_t ips_display_open() {
    // Any additional setup can be done here
    return IPS_DISPLAY_OK;
}

ips_display_status_t ips_display_close() {
    // Any cleanup can be done here
    return IPS_DISPLAY_OK;
}

ips_display_status_t ips_display_write_temp_data(float temperature, float humidity) {
    char temp_val[16];
    char hum_val[16];

    // Format the numeric values using floats
    snprintf(temp_val, sizeof(temp_val), "%.2f C", temperature);
    snprintf(hum_val, sizeof(hum_val), "%.2f %%", humidity);

    // Overwrite only the numeric values on the display
    ST7735_WriteString(80, 10, temp_val, Font_11x18, ST7735_WHITE, ST7735_BLACK);
    ST7735_WriteString(80, 40, hum_val, Font_11x18, ST7735_WHITE, ST7735_BLACK);

    return IPS_DISPLAY_OK;
}
