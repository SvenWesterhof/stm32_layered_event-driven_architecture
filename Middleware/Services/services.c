#include "services.h"
#include "serv_blinky.h"
#include "serv_temperature_sensor.h"
#include "serv_display.h"
#include "serv_current_monitor.h"
#include "protocol_handler.h"

#ifdef ENABLE_UART_TEST
#include "../../Tests/uart_test/serv_uart_test.h"
#endif

void services_init(void)
{
    blinky_init();
    temperature_sensor_init();
    display_init();
    current_monitor_init();
    protocol_handler_init();

#ifdef ENABLE_UART_TEST
    serv_uart_test_init();
#endif
}

void services_run(void)
{
    blinky_run();
    temperature_sensor_run();
    display_run();
    // current_monitor_process();

#ifdef ENABLE_UART_TEST
    serv_uart_test_loop();
#endif
}
