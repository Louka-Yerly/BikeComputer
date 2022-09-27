#include "bike_system.hpp"

#include "mbed_trace.h"
#if MBED_CONF_MBED_TRACE_ENABLE
#define TRACE_GROUP "bike_system"
#endif // MBED_CONF_MBED_TRACE_ENABLE


using namespace static_scheduling;


BikeSystem::BikeSystem():
_wheelRotationCount(0),
_gear(0),
_timer(),
_gearSystemDevice(),
_wheelCounterDevice(),
_resetDevice(_timer),
_lcdDisplay()
{
    _timer.start();
}

void BikeSystem::start() {
  tr_info("Starting Super-Loop with no event");

  while (true) {
    // register the time at the beginning of the cyclic schedule period
    std::chrono::microseconds startTime = _timer.elapsed_time();

    // perform tasks as documented in the timetable
    updateWheelRotationCount();
    checkAndPerformReset();
    updateCurrentGear();
    updateWheelRotationCount();
    updateDisplay(1);
    updateDisplay(2);
    updateWheelRotationCount();
    checkAndPerformReset();
    updateCurrentGear();
    updateWheelRotationCount();
    updateDisplay(3);
    wait_us(100000);

    // register the time at the end of the cyclic schedule period 
    // and print the elapsed time for the period
    std::chrono::microseconds endTime = _timer.elapsed_time();
    tr_debug("Repeating cycle time is %d milliseconds", 
             (int) (endTime.count() - startTime.count()) / 1000);
  }
}

void BikeSystem::updateCurrentGear() {
    _gear = _gearSystemDevice.getCurrentGear();
}
void BikeSystem::updateWheelRotationCount() {
    _wheelRotationCount = _wheelCounterDevice.getCurrentRotationCount();
}
void BikeSystem::checkAndPerformReset() {
    if(_resetDevice.checkReset()) {
        tr_debug("Reset response time is  %i milliseconds", (int)(_timer.elapsed_time()-_resetDevice.getFallTime()).count()/1000); 
        _wheelCounterDevice.reset();
    }
}
void BikeSystem::updateDisplay(uint8_t subTaskIndex) {
    _lcdDisplay.show(_gear, _wheelRotationCount, subTaskIndex);
}
