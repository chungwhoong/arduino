#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS3231 rtc;
char DOW[7][12]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char chk[7][12]={"","*","**","***","****","*****"};
LiquidCrystal_I2C lcd(0x27,16,2); //LCD 연결
DHT11 dht11(7); //DHT11을 7번 핀에 연결
File myFile;  //SD카드의 파일을 받아오는 개체
int tmp_avr=0;  //온도평균값
int hum_avr=0;  //습도평균값
int cnt=0;  //측정횟수
int time_check=0;  //저장할 시각을 체크

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if(!SD.begin(4))
  {
    Serial.println("Initialization failed!");
    while(1);
  }
  
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  rtc.begin();
  DateTime now=rtc.now();
  time_check=now.minute();
}

void loop()
{
  float temp, humi;
  int result=dht11.read(humi, temp);
  cnt++;

  DateTime now=rtc.now();
  int time_temp=now.minute();

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(now.month(),DEC);
  lcd.print("/");
  lcd.print(now.day(),DEC);
  lcd.print("(");
  lcd.print(DOW[now.dayOfTheWeek()]);
  lcd.print(")");
  lcd.print(chk[int(now.second()/10)]);

  lcd.setCursor(0,1);
  lcd.print(now.hour(),DEC);
  lcd.print(":");
  lcd.print(now.minute(),DEC);
  lcd.print(":");
  lcd.print(now.second(),DEC);
  lcd.print(" ");

  lcd.print(int(temp));
  lcd.print("C/");
  lcd.print(int(humi));
  lcd.print("%");

  tmp_avr+=temp;
  hum_avr+=humi;

  if(time_temp!=time_check)
  {
    Serial.print("check");
    myFile=SD.open("record.txt",FILE_WRITE);
    if(myFile)
    {
      Serial.println("Writing time. temp. humi");

      myFile.print(now.month(),DEC);
      myFile.print(",");
      myFile.print(now.day(),DEC);
      myFile.print(",");
      myFile.print(now.hour(),DEC);
      myFile.print(",");
      myFile.print(now.minute(),DEC);
      myFile.print(",");
      myFile.print(float(tmp_avr/cnt));
      myFile.print(char(223));
      myFile.print("C, ");
      myFile.print(int(hum_avr/cnt));
      myFile.println("%");
      myFile.close();
      
      Serial.print(now.month(), DEC);
      Serial.print("/");
      Serial.print(now.day(), DEC);
      Serial.print(" ");
      Serial.print(now.hour(), DEC);
      Serial.print(":");
      Serial.print(now.minute(), DEC);
      Serial.print(" ");
      Serial.print("temp:");
      Serial.print(float(tmp_avr / cnt));
      Serial.print("C, ");
      Serial.print(int(hum_avr / cnt));
      Serial.println("%");
    }
    else
    {
      Serial.println("error opening record.txt");
    }

    time_check=time_temp;
    cnt=0;
    hum_avr=0;
    tmp_avr=0;
    Serial.println("done");
  }
  delay(2000);  
}
