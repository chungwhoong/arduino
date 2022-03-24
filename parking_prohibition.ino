#define TRIG  2
#define ECHO  3
#define RED 5
#define GREEN 6
#define BLUE  7
#define SPEAKER 9

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
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  int distance=pulseIn(ECHO, HIGH)*340/2/10000;
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
  warning(distance);
}


void warning(int distance)
{
  if(distance>5)
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
  }

  if(distance<5)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    tone(SPEAKER, 261.6); delay(200); noTone(SPEAKER); delay(200);
  }
}
