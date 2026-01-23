#include "services.h"
#include "serv_blinky.h"
#include "serv_temperature_sensor.h"
#include "serv_display.h"
#include "serv_current_monitor.h"
#include "protocol_handler.h"
#include "portable_log.h"

#ifdef ENABLE_UART_TEST
#include "../../Tests/uart_test/serv_uart_test.h"
#endif

static const char *TAG = "SERVICES";

void services_init(void)
{

    blinky_init();
    LOG_I(TAG, "Blinky initialized\n");

    temperature_sensor_init();
    LOG_I(TAG, "Temperature sensor initialized\n");
    
    display_init();
    LOG_I(TAG, "Display initialized\n");

    current_monitor_init();
    LOG_I(TAG, "Current monitor initialized\n");

    protocol_handler_init();
    LOG_I(TAG, "Protocol handler initialized\n");

#ifdef ENABLE_UART_TEST
    SEGGER_RTT_printf(0, "Services: Initializing UART test...\n");
    serv_uart_test_init();
    LOG_I(TAG, "UART test service initialized\n");
#endif
}

void services_run(void)
{
    blinky_run();
    temperature_sensor_run();
    display_run();
    current_monitor_process();

#ifdef ENABLE_UART_TEST
    serv_uart_test_loop();
#endif
}
