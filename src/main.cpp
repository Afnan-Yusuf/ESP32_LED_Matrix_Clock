
#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <millisDelay.h>
#include <TaskScheduler.h>

RTC_DS3231 rtc;
char a = ':';
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

char daysOfWeek[7][12] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"};
char buf[20];
void setup()
{
  Serial.begin(115200);

  if (!rtc.begin())
  {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    // while (1);
  }
  // rtc.adjust(DateTime(2024, 3, 21, 3, 0, 0));
  Display.begin();
  Display.setIntensity(0);
  Display.displayText("LED MATRIX CLOCK", PA_CENTER, 100, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
 // Display.displayClear();
}

void loop()
{
  DateTime now = rtc.now();
  Display.setTextAlignment(PA_CENTER);
  sprintf(buf, "%02d%01c%02d", now.hour(), a, now.minute());
  Display.print(buf);
  delay(5000);
  sprintf(buf, "%02d%01c%02d", now.day(), a, now.month());
  Display.print(buf);
  delay(5000);
  sprintf(buf, "%04d", now.year());
  Display.print(buf);
  delay(5000);
}
