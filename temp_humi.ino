//https://blog.naver.com/icbanq/221794766003

#include "DHT.h"
#include <LiquidCrystal.h>


#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);



LiquidCrystal lcd(7,6,5,4,3,2);

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
}

void loop()
{
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
