#include "app_main.h"
#include "control.h"
#include "feature.h"
#include "peripheral.h"

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
