#include "feat_temperature_sensor.h"

#include "main.h" // for temperature_sensor_on_off_GPIO_Port and temperature_sensor_on_off_Pin
#include "peripherals/ath25.h"

ath25_sensor_t* temp_sensor = &default_ath25_sensor;
extern I2C_HandleTypeDef hi2c2;

static uint32_t last_read_time = 0;
static const uint32_t read_interval_ms = 1000; // read every second

void temperature_sensor_init(void)
{
    ath25_init();
    if(ath25_open(temp_sensor, &hi2c2) != HAL_OK) {
        // Handle error
    }
}

void temperature_sensor_run(void)
{
    // Implement the functionality to read temperature data and process it
    ath_data_t data;
    // read temperature sensor and humidity every second   
    uint32_t now = HAL_GetTick();
    if ((now - last_read_time) >= read_interval_ms)
    {
        if(ath25_read(temp_sensor, &data) == HAL_OK) {
            // Successfully read data, process it
            float temperature = data.temperature;
            float humidity = data.humidity;
            // For example, you can log it or update a display
        } else {
            // Handle read error
        }
        last_read_time = now;
    }
}