#include "wheel_counter_device.hpp"


using namespace static_scheduling;

WheelCounterDevice::WheelCounterDevice():
_ticker(), _rotationCount(0)
{
    _ticker.attach(callback(this, &WheelCounterDevice::turn), kWheelRotationTime);
}

void WheelCounterDevice::turn() {
    _rotationCount++;
}

int WheelCounterDevice::getCurrentRotationCount() {
    wait_us(kTaskRunTime.count());
    return _rotationCount;
}

void WheelCounterDevice::reset() {
    _rotationCount = 0;
}