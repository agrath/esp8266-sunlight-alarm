#ifndef DEBUG_H
#define DEBUG_H
#include <HardwareSerial.h>
#define SERIAL_PORT Serial

#define SERIAL_OUTPUT true

#ifndef SERIAL_OUTPUT
#define Debug(...) do { } while(0)
#define DebugF(...) do { } while(0)
#define DebugNoLf(...) do { } while(0)
#else
void Debug(const __FlashStringHelper *ifsh);

void Debug(void);

void Debug(const String &s);

void Debug(const char c[]);

void Debug(char c);

void Debug(unsigned char b, int base);

void Debug(int num, int base);

void Debug(unsigned int num, int base);

void Debug(long num, int base);

void Debug(unsigned long num, int base);

void Debug(double num, int digits);

void Debug(const Printable &x);

void DebugF(const char *format, ...);

void DebugNoLf(const __FlashStringHelper *ifsh);

void DebugNoLf(const String &s);

void DebugNoLf(const char c[]);

void DebugNoLf(char c);

void DebugNoLf(unsigned char b, int base);

void DebugNoLf(int num, int base);

void DebugNoLf(unsigned int num, int base);

void DebugNoLf(long num, int base);

void DebugNoLf(unsigned long num, int base);

void DebugNoLf(double num, int digits);

void DebugNoLf(const Printable &x);
#endif
#endif