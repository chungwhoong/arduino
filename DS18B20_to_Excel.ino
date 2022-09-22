//방수형온도계 엑셀로 받기
//https://works.do/xN1Ifry  PLX-DAQ 다운로드

// DallasTemperature - Version: Latest 
#include <DallasTemperature.h>

// OneWire - Version: Latest 
#include <OneWire.h>

#define ONE_WIRE_BUS  2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup()
{
  sensors.begin();
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time,Temp");
}

void loop()
{
  sensors.requestTemperatures();
  Serial.print("DATA, TIME,");
  Serial.println(sensors.getTempCByIndex(0));
  delay(5000);
}
