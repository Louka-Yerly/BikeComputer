#include "reset_device.hpp"


#if defined(TARGET_DISCO_L475VG_IOT01A) 
#define PUSH_BUTTON BUTTON1
#define POLARITY_PRESSED 0
#endif


using namespace static_scheduling;

ResetDevice::ResetDevice(Timer &timer): 
_resetButton(PUSH_BUTTON), _timer(timer), _fallTime(0ms)
{
    _resetButton.fall(callback(this, &ResetDevice::onFall));
}

void ResetDevice::onFall() {
    _fallTime = _timer.elapsed_time();
}


bool ResetDevice::checkReset() {
    wait_us(kTaskRunTime.count());
    return _resetButton.read() == POLARITY_PRESSED;
}

const std::chrono::microseconds& ResetDevice::getFallTime() {
    return _fallTime;
}