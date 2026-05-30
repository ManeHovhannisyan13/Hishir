#include "TimeManager.h"

// ՈՒՂՂՎԱԾ ԿՈՆՍՏՐՈՒԿՏՈՐ (ընդունում է բոլոր 9 արգումենտները)
TimeManager::TimeManager(
    int* medTimeCount,
    int medYears[][12], int medMonths[][12], int medDays[][12],
    int medHours[][12], int medMinutes[][12],
    String* medNames, String* medTimes, int* medCount
) {
  medTimeCountPtr = medTimeCount;
  medYearsPtr = medYears;
  medMonthsPtr = medMonths;
  medDaysPtr = medDays;
  medHoursPtr = medHours;
  medMinutesPtr = medMinutes;
  medNamesPtr = medNames;
  medTimesPtr = medTimes;
  medCountPtr = medCount;
}

String TimeManager::formatTimeHHMM(const struct tm& ti) {
  char buf[6];
  snprintf(buf, sizeof(buf), "%02d:%02d", ti.tm_hour, ti.tm_min);
  return String(buf);
}

// Ֆունկցիա, որը մշակում է "YYYY-MM-DDTHH:MM" ֆորմատը
bool TimeManager::parseDateTimeISO(
  const String& s,
  int& outY, int& outMon, int& outD, int& outH, int& outM
) {
  int tIndex = s.indexOf('T');
  if (tIndex == -1) return false;

  String datePart = s.substring(0, tIndex); 
  String timePart = s.substring(tIndex + 1); 

  int dash1 = datePart.indexOf('-');
  int dash2 = datePart.indexOf('-', dash1 + 1);
  if (dash1 == -1 || dash2 == -1) return false;

  int colon = timePart.indexOf(':');
  if (colon == -1) return false;

  int year = datePart.substring(0, dash1).toInt();
  int month = datePart.substring(dash1 + 1, dash2).toInt();
  int day = datePart.substring(dash2 + 1).toInt();

  int hour = timePart.substring(0, colon).toInt();
  int min = timePart.substring(colon + 1).toInt();

  if (year < 2020 || month < 1 || month > 12 || day < 1 || day > 31 ||
      hour < 0 || hour > 23 || min < 0 || min > 59) {
    return false;
  }

  outY = year;
  outMon = month;
  outD = day;
  outH = hour;
  outM = min;

  return true;
}

int TimeManager::splitAndStoreTimes(const String& csv, int medIdx) {
  int count = 0;
  int start = 0;

  while (start < (int)csv.length() && count < MAX_TIMES_PER_MED) {
    int comma = csv.indexOf(',', start);
    String part = (comma == -1) ? csv.substring(start) : csv.substring(start, comma);
    part.trim();

    if (part.length() > 0) {
      int y = 0, mon = 0, d = 0, h = 0, m = 0;

      // Կանչում ենք նոր ֆունկցիան
      if (parseDateTimeISO(part, y, mon, d, h, m)) {
        medYearsPtr[medIdx][count] = y;
        medMonthsPtr[medIdx][count] = mon;
        medDaysPtr[medIdx][count] = d;
        medHoursPtr[medIdx][count] = h;
        medMinutesPtr[medIdx][count] = m;
        count++;
      }
    }

    if (comma == -1) break;
    start = comma + 1;
  }

  return count;
}

bool TimeManager::updateSingleMedicine(int medIdx, const String& name, const String& timesCsv) {
  if (medIdx < 0 || medIdx >= MAX_MEDS) {
    return false;
  }

  medNamesPtr[medIdx] = name;
  medTimesPtr[medIdx] = timesCsv;
  medTimeCountPtr[medIdx] = 0;

  for (int t = 0; t < MAX_TIMES_PER_MED; t++) {
    medYearsPtr[medIdx][t] = -1;
    medMonthsPtr[medIdx][t] = -1;
    medDaysPtr[medIdx][t] = -1;
    medHoursPtr[medIdx][t] = -1;
    medMinutesPtr[medIdx][t] = -1;
  }

  medTimeCountPtr[medIdx] = splitAndStoreTimes(medTimesPtr[medIdx], medIdx);

  if (*medCountPtr < (medIdx + 1)) {
    *medCountPtr = medIdx + 1;
  }

  return true;
}

bool TimeManager::syncTimeIfNeeded() {
  if (timeSynced) return true;
  unsigned long now = millis();

  if (now - lastTimeSyncAttemptMs < 3000) {
    return false;
  }

  lastTimeSyncAttemptMs = now;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo, 1500)) {
    Serial.println("NTP sync waiting...");
    return false;
  }

  timeSynced = true;
  Serial.print("NTP synced: ");
  Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");

  return true;
}
