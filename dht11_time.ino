//https://blog.naver.com/icbanq/221794766003  <-참고사이트

#include "DHT.h"
#include <LiquidCrystal.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

ThreeWire myWire(10,9,11); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

  if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

  if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}

void loop()
{
  RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.print(",");

  if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  String data="Temp: "+String(t)+"C, Humi: "+String(h)+"%";
  Serial.println(data);

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("℃");
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print("%");
  delay(10000);  
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
