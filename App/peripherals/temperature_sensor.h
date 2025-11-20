#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

// Initialize the temperature sensor (i2nc setup, GPIOs, etc.)
void temperature_sensor_init();

// Open a connection  and enable the temperature sensor
void temperature_sensor_open();

// Read the current temperature value from the sensor
float temperature_sensor_read();

// Close the connection and disable the temperature sensor
void temperature_sensor_close();

#endif // TEMPERATURE_SENSOR_H

