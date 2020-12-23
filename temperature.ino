#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
RTC_DS3231 rtc;
int sec,minu,hou;

LiquidCrystal_I2C lcd(0x3F,16,2);
dht DHT;

#define DHT11_PIN 7

void showDate(void);
void showTime(void);
void showDay(void); 

void setup(){
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC Module");
    while (1);
  }
  if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

  //lcd.begin();
  //lcd.home();
  //lcd.clear();
  //lcd.print("Hello,NodeMCU");


void loop()
{
  lcd.setCursor(0, 0);
  int chk = DHT.read11(DHT11_PIN);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  lcd.print("T:");
  lcd.print((int)temperature);
  lcd.print(" ");
  lcd.print("H:");
  lcd.print((int)humidity);
  lcd.print("    ");
  showDay();
  lcd.setCursor(0,1);
  now = rtc.now();
  showDate();
  lcd.print(" ");
  showTime();
  delay(1000);
}

void showDate()
 {
  //lcd.setCursor(0,0);
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  //lcd.print('/');
  //lcd.print(now.year()%100);
 }
 void showDay()
 {
  lcd.setCursor(11,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
 }
 void showTime()
 {
  lcd.setCursor(6,1);
  //lcd.print("Time:");
  sec = now.second();
  hou = now.hour();
  minu = now.minute();
  if(hou<10){
    lcd.print(0);
    }
  lcd.print(now.hour());
  lcd.print(':');
  if(minu<10){
    lcd.print(0);
    }
  lcd.print(now.minute());
  lcd.print(':');
  if(sec<10){
    lcd.print(0);
    }
  lcd.print(sec);
  //lcd.print("    ");
 } 
