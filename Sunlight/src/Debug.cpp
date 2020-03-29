#include <stdio.h>
#include <HardwareSerial.h>
#include "Config.h"
#include "Debug.h"

#ifdef SERIAL_OUTPUT
void Debug(const __FlashStringHelper *ifsh)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(ifsh);
  }
}
void Debug(void)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println();
  }
}
void Debug(const String &s)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(s);
  }
}
void Debug(const char c[])
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(c);
  }
}
void Debug(char c)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(c);
  }
}
void Debug(unsigned char b, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(b, base);
  }
}
void Debug(int num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(num, base);
  }
}
void Debug(unsigned int num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(num, base);
  }
}
void Debug(long num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(num, base);
  }
}
void Debug(unsigned long num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(num, base);
  }
}
void Debug(double num, int digits)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(num, digits);
  }
}
void Debug(const Printable &x)
{
  if (debugEnabled)
  {
    SERIAL_PORT.println(x);
  }
}
void DebugF(const char *format, ...)
{
  if (debugEnabled)
  {
    va_list arg;
    va_start(arg, format);
    char temp[128];
    char *buffer = temp;
    vsprintf(temp, format, arg);
    va_end(arg);
    SERIAL_PORT.print(buffer);
  }
}
void DebugNoLf(const __FlashStringHelper *ifsh)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(ifsh);
  }
}
void DebugNoLf(const String &s)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(s);
  }
}
void DebugNoLf(const char c[])
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(c);
  }
}
void DebugNoLf(char c)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(c);
  }
}
void DebugNoLf(unsigned char b, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(b, base);
  }
}
void DebugNoLf(int num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(num, base);
  }
}
void DebugNoLf(unsigned int num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(num, base);
  }
}
void DebugNoLf(long num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(num, base);
  }
}
void DebugNoLf(unsigned long num, int base)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(num, base);
  }
}
void DebugNoLf(double num, int digits)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(num, digits);
  }
}
void DebugNoLf(const Printable &x)
{
  if (debugEnabled)
  {
    SERIAL_PORT.print(x);
  }
}
#endif