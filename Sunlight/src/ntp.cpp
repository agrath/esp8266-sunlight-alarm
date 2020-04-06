#include <ESP8266WiFi.h>
#include <time.h>          // time() ctime()
#include <sys/time.h>      // struct timeval
#include <coredecls.h>     // settimeofday_cb()
#include <debug.h>     
#include <config.h>     
#include <globals.h>     
#include <ntp.h>     

void getUtcFromNtp()
{
  Debug(F("getUtcFromNtp"));
  timeCallbackInvoked = false;
  configTime(0, 0, NTP_SERVER);

  // set time from RTC
  // Normally you would read the RTC to eventually get a current UTC time_t
  // this is faked for now.
  time_t rtc_time_t = 1541267183; // fake RTC time for now
  timezone tz = { 0, 0};
  timeval tv = { rtc_time_t, 0};

  // DO NOT attempt to use the timezone offsets
  // The timezone offset code is really broken.
  // if used, then localtime() and gmtime() won't work correctly.
  // always set the timezone offsets to zero and use a proper TZ string
  // to get timezone and DST support.

  // set the time of day and explicitly set the timezone offsets to zero
  // as there appears to be a default offset compiled in that needs to
  // be set to zero to disable it.
  settimeofday(&tv, &tz);

  // set up TZ string to use a POSIX/gnu TZ string for local timezone
  // TZ string information:
  setenv("TZ", NTP_TZ, 1);
  tzset(); // save the TZ variable

  settimeofday_cb(timeCallback);
  int16_t attempts = 0;
  while (!timeCallbackInvoked) //10 sec
  {
    attempts++;
    time(&utc);
    delay(100);
    if (attempts > 100)
    {
      break;
    }
  }
  if (!timeCallbackInvoked)
  {
    //ntp timeout
    Debug(F("NTP timeout, restarting..."));
    ESP.restart();
  }
}

void timeCallback()
{
  Debug(F("timeCallback"));
  gettimeofday(&utcVal, NULL);
  utc = (time_t)utcVal.tv_sec;
  if (debugEnabled)
  {
    displayFormattedTime();
  }
  timeCallbackInvoked = true;
}

void displayFormattedTime()
{
  Debug(F("displayFormattedTime"));
  struct tm *timeInfo = localtime(&utc);
  strftime(sharedCharacterBuffer, 80, "%d %B %Y %H:%M:%S ", timeInfo);
  DebugF((const char *)F("Local time fetched as %s\n"), sharedCharacterBuffer);
}

struct tm* getCurrentLocalTime()
{
  gettimeofday(&utcVal, NULL);
  utc = (time_t)utcVal.tv_sec;
  struct tm *timeInfo = localtime(&utc);
  return timeInfo;
}