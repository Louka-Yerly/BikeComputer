#include "lcd_display.hpp"


using namespace static_scheduling;


LCDDisplay::LCDDisplay()
{
}

void LCDDisplay::show(uint8_t currentGear, uint32_t currentRotationCount, uint8_t subTaskIndex) {
    if(subTaskIndex == 1) {
        printf("=================\n");
    }  
    if(subTaskIndex == 2) {
        printf("Rotation: %i\n", currentRotationCount);
    }
    else {
        printf("Gear:     %i\n", currentGear);
    }
    wait_us(kTaskRunTime.count()/kNbrOfSubTasks);
}