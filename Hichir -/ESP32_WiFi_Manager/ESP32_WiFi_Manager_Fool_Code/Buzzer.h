#ifndef Buzzer_h
#define Buzzer_h

#include "Device.h"

class Buzzer : public Device {
  private:
      static const bool BUZZER_ACTIVE_LOW = false;
      bool buzzerBlinkState = false;
      unsigned long buzzerPrevMs = 0;
      const int buzzerInterval = 300;

  public:
      void init();
      void blink();
      void on();
      void off();
};

#endif
