#include "app_main.h"
#include "services.h"
#include "event_bus.h"
#include "portable_log.h"
#include "rtt_logging_test.h"
#include "systemview_demo.h"

static const char *TAG = "APP";

void app_init(void)
{
    LOG_I(TAG, "Application initializing...");
    systemview_mark_event("App Init Start");

    // Initialize event bus first
    event_bus_init();
    LOG_I(TAG, "Event bus initialized");
    systemview_mark_event("Event Bus Ready");

    // Initialize services (including display service which subscribes to events)
    services_init();
    LOG_I(TAG, "Services initialized");
    systemview_mark_event("Services Ready");

    LOG_I(TAG, "About to call rtt_test_logging()...");
    // Test RTT logging now that everything is stable
    // TEMPORARILY DISABLED: rtt_test_logging();
    LOG_I(TAG, "RTT test SKIPPED");

    LOG_I(TAG, "About to call systemview_demo_start()...");
    // Start SystemView demonstration
    systemview_demo_start();
    LOG_I(TAG, "SystemView demo start completed");

    LOG_I(TAG, "Application initialized successfully");
    systemview_mark_event("App Init Complete");
}

void app_run(void)
{
    static uint32_t run_counter = 0;
    
    // Mark application runtime phase less frequently
    if (run_counter % 5000 == 0) {  // Only every 5000 calls
        systemview_mark_event("App Runtime");
    }
    run_counter++;
    
    // Run services (they publish events)
    services_run();

    // Process any pending events
    event_bus_process();
    
    // Periodic SystemView demonstration
    systemview_demo_log_tasks();
}
