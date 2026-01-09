#include "app_main.h"
#include "control.h"
#include "services.h"
#include "peripheral.h"

void app_init(void)
{
    //Peripheral_Init();
    //Control_Init();
    services_init();
    
}

void app_run(void)
{
    //Peripheral_Run();
    //Control_Run();
    services_run();

}
