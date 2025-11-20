#include "app.h"
#include "control/control.h"
#include "features/feature.h"
#include "peripherals/peripheral.h"

void app_init(void)
{
    //Peripheral_Init();
    //Control_Init();
    feature_init();
    
}

void app_run(void)
{
    //Peripheral_Run();
    //Control_Run();
    feature_run();

}
