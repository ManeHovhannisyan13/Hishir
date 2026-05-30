#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <Arduino.h>
#include "time.h"

class TimeManager {
public:
    static const int MAX_MEDS = 7;
    static const int MAX_TIMES_PER_MED = 12;

    // Կոնստրուկտորում ավելացնում ենք նոր զանգվածների հղումները (pointers)
    TimeManager(int* medTimeCount, 
                int medYears[][12], int medMonths[][12], int medDays[][12],
                int medHours[][12], int medMinutes[][12], 
                String* medNames, String* medTimes, int* medCount);

    int splitAndStoreTimes(const String& csv, int medIdx);
    bool updateSingleMedicine(int medIdx, const String& name, const String& timesCsv);
    bool syncTimeIfNeeded();
    String formatTimeHHMM(const struct tm& ti);
    
    // Ֆունկցիա ISO DateTime (YYYY-MM-DDTHH:MM) ֆորմատը կարդալու համար
    bool parseDateTimeISO(const String& s, int& outY, int& outMon, int& outD, int& outH, int& outM);

private:
    int* medTimeCountPtr;
    int (*medYearsPtr)[12];
    int (*medMonthsPtr)[12];
    int (*medDaysPtr)[12];
    int (*medHoursPtr)[12];
    int (*medMinutesPtr)[12];
    String* medNamesPtr;
    String* medTimesPtr;
    int* medCountPtr;

    bool timeSynced = false;
    unsigned long lastTimeSyncAttemptMs = 0;
    const long gmtOffset_sec = 4 * 3600;
    const int daylightOffset_sec = 0;
    const char* ntpServer = "pool.ntp.org";
};

#endif
