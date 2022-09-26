//방수형온도계 엑셀로 받기
//https://works.do/xN1Ifry  PLX-DAQ 다운로드

// DallasTemperature - Version: Latest 
#include <DallasTemperature.h>

// OneWire - Version: Latest 
#include <OneWire.h>

#define ONE_WIRE_BUS  2
#define TWO_WIRE_BUS  3

OneWire oneWire(ONE_WIRE_BUS);
OneWire twoWire(TWO_WIRE_BUS);

DallasTemperature sensors1(&oneWire);
DallasTemperature sensors2(&twoWire);

void setup()
{
  sensors1.begin();
  sensors2.begin();
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Temp1, Temp2");
}

void loop()
{
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
  Serial.print("DATA, TIME,");
  Serial.print(sensors1.getTempCByIndex(0));
  Serial.print(",");
  Serial.println(sensors2.getTempCByIndex(0));
  delay(5000);
}
