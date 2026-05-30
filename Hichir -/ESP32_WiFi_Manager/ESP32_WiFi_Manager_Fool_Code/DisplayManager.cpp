#include "DisplayManager.h"

DisplayManager::DisplayManager(LiquidCrystal_I2C* lcd, TimeManager* timeManager, String* medNames) {
  lcdPtr = lcd;
  timeManagerPtr = timeManager;
  medNamesPtr = medNames;
}

void DisplayManager::clearSafe() {
  lcdPtr->clear();
  lcdPtr->setCursor(0, 0);
}

void DisplayManager::writeLine(int row, const String& text) {
  String t = text;

  if (t.length() > 16) {
    t = t.substring(0, 16);
  }

  while (t.length() < 16) {
    t += ' ';
  }

  lcdPtr->setCursor(0, row);
  lcdPtr->print(t);
}

void DisplayManager::refresh(const struct tm& timeinfo, bool alarmActive, bool silenced, bool matchNow, int medIdx) {
  String timeStr = timeManagerPtr->formatTimeHHMM(timeinfo);

  if (alarmActive && silenced) {
    writeLine(0, "");
    writeLine(1, timeStr);
  }
  else if (alarmActive && matchNow && medIdx >= 0) {
    String top = "M" + String(medIdx + 1) + " ";
    top += medNamesPtr[medIdx];
    top.trim();

    if (top.length() > 16) {
      top = top.substring(0, 16);
    }

    writeLine(0, top);
    writeLine(1, timeStr);
  }
  else {
    writeLine(0, "");
    writeLine(1, timeStr);
  }
}

// ԱՎԵԼԱՑՐԵՔ ԱՅՍ ՖՈՒՆԿՑԻԱՆ ՖԱՅԼԻ ՎԵՐՋՈՒՄ
void DisplayManager::update() {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    // 1. Պատրաստում ենք ամսաթվի տեքստը (Օրինակ՝ 2026-05-25)
    char dateBuf[11];
    snprintf(dateBuf, sizeof(dateBuf), "%04d-%02d-%02d", 
             timeinfo.tm_year + 1900, 
             timeinfo.tm_mon + 1, 
             timeinfo.tm_mday);
             
    // 2. Պատրաստում ենք ժամի տեքստը՝ վայրկյաններով (Օրինակ՝ 20:39:05)
    char timeBuf[9];
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d:%02d", 
             timeinfo.tm_hour, 
             timeinfo.tm_min, 
             timeinfo.tm_sec);

    // 3. Տպում ենք էկրանին (առաջին տողում ամսաթիվը, երկրորդում՝ ժամը)
    writeLine(2, String(dateBuf) + " " + String(timeBuf));
  } else {
    writeLine(0, "Time Error");
  }
}
