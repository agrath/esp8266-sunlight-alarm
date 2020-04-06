#include <TimeHelper.h>
#include <time.h>
#include <Globals.h>
#include <Debug.h>

bool CheckAlarm(AlarmData *alarm, tm *currentLocalTime)
{
    strftime(sharedCharacterBuffer, 80, "%d %B %Y %H:%M:%S ", currentLocalTime);
    DebugF((const char *)F("[CheckAlarm] Local time fetched as %s\n"), sharedCharacterBuffer);
    
    //todo: dow constants are not bitwise, need my own enum dowFlagSaturday etc so I can bitwise it 0x01 0x02 0x04 0x08 0x...
    bool dayOfWeekIsValid = ((alarm->Days) & (currentLocalTime->tm_wday) != 0x00);
    if (dayOfWeekIsValid)
    {
        DebugF((const char *)F("[CheckAlarm] Correct weekday %d\n"), currentLocalTime->tm_wday);
    }
    else
    {
        DebugF((const char *)F("[CheckAlarm] Invalid weekday %d\n"), currentLocalTime->tm_wday);
    }
}