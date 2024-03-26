
#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
// #include <millisDelay.h>
// #include <TaskScheduler.h>
bool b = false;
RTC_DS3231 rtc;
char a = ':';
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

String all ;

char daysOfWeek[7][12] = {
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"};
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
  // rtc.adjust(DateTime(2024, 3, 26, 12, 12, 0));
  Display.begin();
  Display.displayText("LED MATRIX CLOCK", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!Display.displayAnimate()){
  Display.displayAnimate();
 }
  Display.setIntensity(15);

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
  Display.print(daysOfWeek[now.dayOfTheWeek()]);
  delay(5000);
  sprintf(buf, "%04d", now.year());
  Display.print(buf);
  delay(5000);
  all = now.hour() + now.minute() + now.second();
  Serial.println(all);
  
}
