#include "KeypadController.h"

extern bool alarmSilencedByButton;

KeypadController::KeypadController() {
  keypad = new Keypad(
    makeKeymap(keys),
    rowPins,
    colPins,
    ROWS,
    COLS
  );
}

// ԱՎԵԼԱՑՐԵՔ ԱՅՍ ՖՈՒՆԿՑԻԱՆ
char KeypadController::getKey() {
  return keypad->getKey();
}
