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
    extern int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);

    SEGGER_RTT_printf(0, "Services: Initializing blinky...\n");
    blinky_init();
    SEGGER_RTT_printf(0, "Services: Blinky OK\n");

    SEGGER_RTT_printf(0, "Services: Initializing temperature sensor...\n");
    // TEMPORARILY DISABLED: temperature_sensor_init() crashes (I2C issue at 216MHz?)
    // temperature_sensor_init();
    SEGGER_RTT_printf(0, "Services: Temperature sensor SKIPPED (disabled for debugging)\n");

    SEGGER_RTT_printf(0, "Services: Initializing display...\n");
    display_init();
    SEGGER_RTT_printf(0, "Services: Display OK\n");

    SEGGER_RTT_printf(0, "Services: Initializing current monitor...\n");
    current_monitor_init();
    SEGGER_RTT_printf(0, "Services: Current monitor OK\n");

    SEGGER_RTT_printf(0, "Services: Initializing protocol handler...\n");
    protocol_handler_init();
    SEGGER_RTT_printf(0, "Services: Protocol handler OK\n");

#ifdef ENABLE_UART_TEST
    SEGGER_RTT_printf(0, "Services: Initializing UART test...\n");
    serv_uart_test_init();
    SEGGER_RTT_printf(0, "Services: UART test OK\n");
#endif
}

void services_run(void)
{
    blinky_run();
    // TEMPORARILY DISABLED: temperature_sensor_run() (sensor init was skipped)
    // temperature_sensor_run();
    display_run();
    // current_monitor_process();

#ifdef ENABLE_UART_TEST
    serv_uart_test_loop();
#endif
}
