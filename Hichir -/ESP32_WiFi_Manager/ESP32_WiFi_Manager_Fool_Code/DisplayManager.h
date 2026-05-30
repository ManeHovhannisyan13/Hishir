#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "TimeManager.h"

class DisplayManager {
  public:
    DisplayManager(LiquidCrystal_I2C* lcd, TimeManager* timeManager, String* medNames);

    void clearSafe();
    void writeLine(int row, const String& text);
    void refresh(const struct tm& timeinfo, bool alarmActive, bool silenced, bool matchNow, int medIdx);
    
    // ԱՎԵԼԱՑՐԵՔ ԱՅՍ ՏՈՂԸ
    void update();

  private:
    LiquidCrystal_I2C* lcdPtr;
    TimeManager* timeManagerPtr;
    String* medNamesPtr;
};

#endif
