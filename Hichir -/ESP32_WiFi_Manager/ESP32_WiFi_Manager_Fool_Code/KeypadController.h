#ifndef KeypadController_h
#define KeypadController_h

#include <Arduino.h>
#include <Keypad.h>
#include "Buzzer.h"
#include "ServoController.h"

class KeypadController {
  public:
     KeypadController();
    
    // ԱՎԵԼԱՑՎԱԾ Է ԱՅՍ ՏՈՂԸ, որպեսզի main.cpp-ն կարողանա կարդալ սեղմված կոճակը
    char getKey();

    bool alarmSilencedByButton = false;

  private:
    static const byte ROWS = 4;
    static const byte COLS = 4;

    char keys[ROWS][COLS] = {
      { '1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
    };

    byte rowPins[ROWS] = {13, 12, 14, 27};
    byte colPins[COLS] = {26, 25, 33, 32};

    Keypad* keypad;

};

#endif
