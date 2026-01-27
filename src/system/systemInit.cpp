#include "systemInit.h"


void initSystem()
{
    initSystemResources();
    initTofSensors();
    encoder_init();
}
