#include "app.h"
#include "control/control.h"
#include "features/feature.h"
#include "peripherals/peripheral.h"

void App_Init(void)
{
    //Peripheral_Init();
    //Control_Init();
    Feature_Init();
    
}

void App_Run(void)
{
    //Peripheral_Run();
    //Control_Run();
    Feature_Run();

}
