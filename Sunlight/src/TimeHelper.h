#include <time.h>
#include <debug.h>

#define SECS_PER_MIN  ((time_t)(60UL))
#define SECS_PER_HOUR ((time_t)(3600UL))

#define CreateTimeFromHourMinuteSecond(_hr_, _min_, _sec_) (_hr_ * SECS_PER_HOUR + _min_ * SECS_PER_MIN + _sec_)

struct AlarmData
{
  unsigned short Days;
  time_t AlarmTime;
  time_t WakePeriod;
  bool IsInProgress;

};

bool CheckAlarm(AlarmData *alarm, tm *currentLocalTime);