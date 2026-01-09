#ifndef IPS_DISPLAY_H
#define IPS_DISPLAY_H

#include "hal_spi.h"

typedef enum {
    IPS_DISPLAY_OK = 0,
    IPS_DISPLAY_ERROR
} ips_display_status_t;

ips_display_status_t ips_display_init();
ips_display_status_t ips_display_open();
ips_display_status_t ips_display_close();

ips_display_status_t ips_display_write_temp_data(float temperature, float humidity);


#endif // IPS_DISPLAY_H
