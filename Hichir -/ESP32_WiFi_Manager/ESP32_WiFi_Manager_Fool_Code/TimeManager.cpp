#include "TimeManager.h"

// Կոնստրուկտորը պահում է դեղերի ժամանակացույցի զանգվածների հղումները։
TimeManager::TimeManager(
    int* medTimeCount,
    int medWeekdays[][12], int medHours[][12], int medMinutes[][12],
    String* medNames, String* medTimes, int* medCount
) {
  medTimeCountPtr = medTimeCount;
  medWeekdaysPtr = medWeekdays;
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

// Ֆունկցիա, որը մշակում է "W0T08:00" ... "W6T23:59" ֆորմատը
bool TimeManager::parseWeekdayTime(
  const String& s,
  int& outWeekday, int& outH, int& outM
) {
  int tIndex = s.indexOf('T');
  if (tIndex == -1) return false;

  String weekdayPart = s.substring(0, tIndex);
  String timePart = s.substring(tIndex + 1); 

  if (weekdayPart.length() < 2 || weekdayPart.charAt(0) != 'W') return false;

  int colon = timePart.indexOf(':');
  if (colon == -1) return false;

  int weekday = weekdayPart.substring(1).toInt();
  int hour = timePart.substring(0, colon).toInt();
  int min = timePart.substring(colon + 1).toInt();

  if (weekday < 0 || weekday > 6 || hour < 0 || hour > 23 || min < 0 || min > 59) {
    return false;
  }

  outWeekday = weekday;
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
      int weekday = -1, h = 0, m = 0;

      if (parseWeekdayTime(part, weekday, h, m)) {
        medWeekdaysPtr[medIdx][count] = weekday;
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
    medWeekdaysPtr[medIdx][t] = -1;
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
