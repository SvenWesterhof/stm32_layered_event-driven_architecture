#include "serv_temperature_sensor.h"
#include "event_bus.h"
#include "service_events.h"
#include "ath25.h"
#include "bsp.h"

ath25_sensor_t* temp_sensor = &default_ath25_sensor;

static uint32_t last_read_time = 0;
static const uint32_t read_interval_ms = 1000; // read every second

void temperature_sensor_init(void)
{
    ath25_init();
    if(ath25_open(temp_sensor, BSP_Get_TempSensor_I2C()) != HAL_I2C_OK) {
        // Handle error
    }
}

void temperature_sensor_run(void)
{
    // Read temperature sensor and humidity every second   
    uint32_t now = hal_get_tick();
    if ((now - last_read_time) >= read_interval_ms)
    {
        ath_data_t data;
        temperature_data_t temp_event_data;
        
        if(ath25_read(temp_sensor, &data) == HAL_I2C_OK) {
            // Successfully read data, publish event
            temp_event_data.temperature = data.temperature;
            temp_event_data.humidity = data.humidity;
            temp_event_data.sensor_ok = 1;
            
            // Publish event to notify subscribers
            event_bus_publish(EVENT_TEMPERATURE_UPDATED, &temp_event_data, sizeof(temperature_data_t));
        } else {
            // Handle read error - publish error event
            temp_event_data.temperature = 0.0f;
            temp_event_data.humidity = 0.0f;
            temp_event_data.sensor_ok = 0;
            
            event_bus_publish(EVENT_SENSOR_ERROR, &temp_event_data, sizeof(temperature_data_t));
        }
        last_read_time = now;
    }
}
