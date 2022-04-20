#define RAY A0
#define RED 5
#define SPEAKER 9

unsigned long previousTime=0;
unsigned long interval=8000;

long distance=0;

long distanceMeasure();

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
}

void loop()
{
  unsigned long currentTime=millis();
  if(currentTime-previousTime>=interval)
  {    
    previousTime=currentTime;
    
    distance=distanceMeasure();
    while(distance<5)
    {
      digitalWrite(RED, HIGH);
      tone(SPEAKER, 261.6); delay(200); noTone(SPEAKER); delay(200);
      distance=distanceMeasure();
    }
  }
   digitalWrite(RED, LOW);
}

long distanceMeasure()
{
  int value=analogRead(RAY);
  distance=(6787.0/(value-3.0)-4.0);
  return distance;
}
