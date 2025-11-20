#ifndef ATH25_H
#define ATH25_H

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"
#include "pinout.h"
#include <stdbool.h>

// sensor is -40 to 80 degrees with an resolution of 0.01 degrees conversion -> (St / 2^20) * 200 - 50

typedef struct {
    bool initialized;
    I2C_HandleTypeDef *hi2c;   // I2C handle
    uint8_t i2c_address;  // I2C address of the temperature sensor
    GPIO_TypeDef *power_port;        // power control pin
    uint16_t power_pin;              // power control pin
    uint8_t resolution;              // sensor resolution (bits)
} ath25_sensor_t;

ath25_sensor_t default_ath25_sensor = {
    .initialized = false,
    .hi2c = NULL,
    .i2c_address = 0x38 << 1, // Example I2C address
    .power_port = TEMP_SENSOR_ON_OFF_PORT,
    .power_pin = TEMP_SENSOR_ON_OFF_PIN,
};

typedef struct {
    float temperature;
    float humidity;
}ath_data_t;

#define MAX_ATH25_I2C_TRANSFER_TIME 100

// Initialize the temperature sensor (i2nc setup, GPIOs, etc.)
void ath25_init();

// Open a connection  and enable the temperature sensor
HAL_StatusTypeDef ath25_open(ath25_sensor_t *sensor, I2C_HandleTypeDef *hi2c);

// Read the current temperature value from the sensor
HAL_StatusTypeDef ath25_read(ath25_sensor_t *sensor, ath_data_t *data);

// Close the connection and disable the temperature sensor
HAL_StatusTypeDef ath25_close(ath25_sensor_t *sensor);

#endif // ATH25_H

