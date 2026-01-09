#include "app_main.h"
#include "services.h"
#include "event_bus.h"

void app_init(void)
{
    // Initialize event bus first
    event_bus_init();
    
    // Initialize services (including display service which subscribes to events)
    services_init();
}

void app_run(void)
{
    // Run services (they publish events)
    services_run();
    
    // Process any pending events
    event_bus_process();
}
