#include "HX711.h" 

HX711 scale(10, 9);

#define calibration_factor -7050.0 
#define TRIG  2
#define ECHO  3
#define RED 5
#define GREEN 6
#define BLUE  7
#define SPEAKER 8



unsigned long previousTime=0;
unsigned long interval=8000;

long distance=0;
long weight=0;

long distanceMeasure();

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop()
{
  
  unsigned long currentTime=millis();
  if(currentTime-previousTime>=interval)
  {    
    previousTime=currentTime;
    weight=scale.get_units();
    distance=distanceMeasure();
    Serial.println(scale.get_units());
    Serial.println(distance);
    while(distance<5 && weight<0.0)
    {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      tone(SPEAKER, 261.6); delay(200); noTone(SPEAKER); delay(200);
      weight=scale.get_units();
      distance=distanceMeasure();
    }
  }
   digitalWrite(GREEN, HIGH);
   digitalWrite(RED, LOW);
   digitalWrite(BLUE, LOW); 
}

long distanceMeasure()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long distance=pulseIn(ECHO, HIGH)*340/2/10000;
  return distance;
}
