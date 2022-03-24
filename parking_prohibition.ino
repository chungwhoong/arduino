#define TRIG  2
#define ECHO  3
#define RED 5
#define GREEN 6
#define BLUE  7
#define SPEAKER 9

unsigned long previousTime=0;
unsigned long interval=8000;

long distance=0;

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
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      tone(SPEAKER, 261.6); delay(200); noTone(SPEAKER); delay(200);
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
