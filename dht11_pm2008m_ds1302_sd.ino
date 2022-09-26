#include <SPI.h>
#include <Wire.h>
#include <DHT11.h>
#include <SD.h>
#include <DS1302.h>
#include <pm2008_i2c.h>

PM2008_I2C pm2008_i2c;

#define CLK_PIN 6
#define DATA_PIN  7
#define RST_PIN 8

DS1302 rtc(RST_PIN, DATA_PIN, CLK_PIN);
DHT11 dht11(3);
File myFile;  //SD카드의 파일을 받아오는 개체

void setup()
{
  #ifdef PM2008N
  // wait for PM2008N to be changed to I2C mode
  delay(10000);
  #endif
  pm2008_i2c.begin();
  pm2008_i2c.command();
  delay(1000);

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if(!SD.begin(4))
  {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Card initialize");
}

void loop()
{
  float temp, humi;
  int result=dht11.read(humi, temp);
  
  uint8_t ret = pm2008_i2c.read();
  if(ret == 0)
  {
    myFile=SD.open("data2.txt",FILE_WRITE);
    if(myFile)
     {
       myFile.print(rtc.getDateStr());     
       myFile.print(",");
       myFile.print(rtc.getTimeStr());
       myFile.print(",");
       myFile.print(temp);
       myFile.print(",");
       myFile.print(humi);
       myFile.print(",");
       myFile.print(pm2008_i2c.pm1p0_grimm);
       myFile.print(",");
       myFile.println(pm2008_i2c.pm10_grimm);
       myFile.close();
        
       Serial.print(rtc.getDateStr());     
       Serial.print(",");
       Serial.print(rtc.getTimeStr());
       Serial.print(",");
       Serial.print(temp);
       Serial.print(",");
       Serial.print(humi);
       Serial.print(",");
       Serial.print(pm2008_i2c.pm1p0_grimm);
       Serial.print(",");
       Serial.print(pm2008_i2c.pm2p5_grimm);     
       Serial.print(",");
       Serial.println(pm2008_i2c.pm10_grimm);
     }
    else
     {
       Serial.println("error opening record.txt");
     }
   }
  delay(10000);  
}
