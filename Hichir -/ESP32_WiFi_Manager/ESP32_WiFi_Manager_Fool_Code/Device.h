#ifndef Device_h
#define Device_h

#include "Arduino.h"

class Device {
protected:
    int _pin; // Փինի համարը, որը հասանելի կլինի նաև ժառանգներին

public:
    Device(int pin = -1) {
        _pin = pin;
    }
    void setPin(int pin) {
        _pin = pin;
    }

    int getPin() {
        return _pin;
    }
};

#endif
