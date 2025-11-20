#include "ath25.h"

#include "pinout.h"

void ath25_init() {
    // Initialize I2C, GPIOs, etc. for the temperature sensor
}

static uint8_t ath25_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF;

    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;  // polynomial: x8 + x5 + x4 + 1 (0x31)
            else
                crc <<= 1;
        }
    }
    return crc;
}

HAL_StatusTypeDef ath25_open(ath25_sensor_t *sensor, I2C_HandleTypeDef *hi2c) {
    uint8_t cmd = 0x71; 
    uint8_t status; 

    sensor->hi2c = hi2c;
    sensor->initialized = false; 
    
    // Power on the sensor
    HAL_GPIO_WritePin(sensor->power_port, sensor->power_pin, GPIO_PIN_SET);
    HAL_Delay(100); // wait for sensor to power up

    // Check sensor status
    if (HAL_I2C_Master_Transmit(sensor->hi2c, sensor->i2c_address, &cmd, 1, MAX_ATH25_I2C_TRANSFER_TIME) != HAL_OK) {
        return HAL_ERROR;
    }
    if (HAL_I2C_Master_Receive(sensor->hi2c, sensor->i2c_address, &status, 1, MAX_ATH25_I2C_TRANSFER_TIME) != HAL_OK) {
        return HAL_ERROR;
    }

        // Check calibration bits must be 0x18
    if ((status & 0x18) != 0x18) {
        // Normally you'd write registers 0x1B, 0x1C, 0x1E here
        // Manufacturer: "see sample program". Many modules ship pre-calibrated.
        return HAL_ERROR;
    }
    sensor->initialized = true;
    return HAL_OK;
}

HAL_StatusTypeDef ath25_read(ath25_sensor_t *sensor, ath_data_t *data) {
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t recv[7];
    // Read temperature value from the sensor
    if (sensor->initialized == false) {
        return HAL_ERROR;
    }

    if (HAL_I2C_Master_Transmit(sensor->hi2c, sensor->i2c_address, cmd, 3, MAX_ATH25_I2C_TRANSFER_TIME) != HAL_OK) {
        return HAL_ERROR;
    }

    HAL_Delay(80); // wait for measurement to complete

    if (HAL_I2C_Master_Receive(sensor->hi2c, sensor->i2c_address, recv, 7, MAX_ATH25_I2C_TRANSFER_TIME) != HAL_OK) {
        return HAL_ERROR;
    }

        // Check if busy bit clear
    if (recv[0] & 0x80)
        return HAL_BUSY;

    // Verify CRC
    if (ath25_crc8(recv, 6) != recv[6]) {
        return HAL_ERROR;
    }

    //combine bytes to get raw temperature and humidity
    uint32_t raw_temp = ((uint32_t)(recv[3] & 0x0F) << 16) | ((uint32_t)recv[4] << 8) | (uint32_t)recv[5];
    uint32_t raw_hum = ((uint32_t)recv[1] << 12) | ((uint32_t)recv[2] << 4) | ((uint32_t)(recv[3] >> 4));

    // Convert raw values to physical values
    data->temperature = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f; // -50 to 150 C
    data->humidity = ((float)raw_hum / 1048576.0f) * 100.0f; // 0 to 100 %

    return HAL_OK;
}

HAL_StatusTypeDef ath25_close(ath25_sensor_t *sensor) {
    // Close connection to the temperature sensor
    if (sensor->initialized == false) {
        return HAL_ERROR;
    }
    // Power off the sensor
    HAL_GPIO_WritePin(sensor->power_port, sensor->power_pin, GPIO_PIN_RESET);
    sensor->initialized = false;
    return HAL_OK;
}