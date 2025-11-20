#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"
#include "pinout.h"

// sensor is -40 to 80 degrees with an resolution of 0.01 degrees conversion -> (St / 2^20) * 200 - 50

typedef struct {
    uint8_t i2c_address;  // I2C address of the temperature sensor
    GPIO_TypeDef *power_port;        // power control pin
    uint16_t power_pin;              // power control pin
    uint8_t resolution;              // sensor resolution (bits)
    float last_temperature;          // cached value
} temp_sensor_t;

temp_sensor_t default_temp_sensor = {
    .i2c_address = 0x38, // Example I2C address
    .power_port = TEMP_SENSOR_ON_OFF_PORT,
    .power_pin = TEMP_SENSOR_ON_OFF_PIN,
    .resolution = 20, // 20-bit resolution
    .last_temperature = 0.0f
};

// Initialize the temperature sensor (i2nc setup, GPIOs, etc.)
void temperature_sensor_init();

// Open a connection  and enable the temperature sensor
void temperature_sensor_open();

// Read the current temperature value from the sensor
float temperature_sensor_read(I2C_HandleTypeDef *hi2c, temp_sensor_t *sensor, float *temperature);

// Close the connection and disable the temperature sensor
void temperature_sensor_close();

#endif // TEMPERATURE_SENSOR_H

