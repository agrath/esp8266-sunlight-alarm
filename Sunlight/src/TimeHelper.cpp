#include <TimeHelper.h>
#include <time.h>
#include <Globals.h>
#include <Debug.h>

bool CheckAlarm(AlarmData *alarm, tm *currentLocalTime)
{
    strftime(sharedCharacterBuffer, 80, "%d %B %Y %H:%M:%S ", currentLocalTime);
    DebugF((const char *)F("[CheckAlarm] Local time fetched as %s\n"), sharedCharacterBuffer);

    bool dayOfWeekIsValid = MatchDayOfWeekToCombinedFlagValue(alarm->Days, (timeDayOfWeek_t)(currentLocalTime->tm_wday+1));
    if (dayOfWeekIsValid)
    {
        DebugF((const char *)F("[CheckAlarm] Correct weekday %d\n"), currentLocalTime->tm_wday);
    }
    else
    {
        DebugF((const char *)F("[CheckAlarm] Invalid weekday %d\n"), currentLocalTime->tm_wday);
    }
}

unsigned short GetFlagValueForDayOfWeek(timeDayOfWeek_t dayOfWeek)
{
    switch (dayOfWeek)
    {
    case dowSunday:
        return 1;
    case dowMonday:
        return 2;
    case dowTuesday:
        return 4;
    case dowWednesday:
        return 8;
    case dowThursday:
        return 16;
    case dowFriday:
        return 32;
    case dowSaturday:
        return 64;
    }
    return 128;
}

bool MatchDayOfWeekToCombinedFlagValue(unsigned short alarmFlagValue, timeDayOfWeek_t dayOfWeek)
{
    unsigned short dayOfWeekFlagValue =  GetFlagValueForDayOfWeek(dayOfWeek);
    DebugF("[CheckAlarm] MatchDayOfWeekToCombinedFlagValue %d dayOfWeek %d dayOfWeekBits %d\n", alarmFlagValue, dayOfWeek, dayOfWeekFlagValue);
    return ((alarmFlagValue & dayOfWeekFlagValue) != 0x00);   
}
