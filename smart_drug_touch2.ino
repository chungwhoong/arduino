#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

#define TOUCH 4
#define aMotor  5
#define bMotor  6
#define cMotor  12
#define dMotor  13

#define SWITCH  11

int flag=0;
int drug_type=10;
byte data=0;

SoftwareSerial mp3_serial(10,11);
unsigned long startTime;
unsigned long touchTime;
int count=0;

boolean a_motorStatus = false;
boolean b_motorStatus = false;

void speaker(int tabcount);

DFRobotDFPlayerMini mp3_player;

void setup()
{
  Serial.begin(9600);

  pinMode(aMotor, OUTPUT);
  pinMode(bMotor, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.println("Smart Drug");
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  
  mp3_serial.begin(9600);

  mp3_player.begin(mp3_serial);
  delay(1000);
  mp3_player.volume(20);  
  pinMode(TOUCH,INPUT);
}

void loop()
{
  if(digitalRead(SWITCH)==HIGH)
  {
    if(flag==0) flag=1;
  }
  else
  {
    if(flag==1)
    {
      if(drug_type==10) drug_type=20;
      else drug_type=10;
      flag=0;
    }
  }
  delay(100);
  
  display.setCursor(10,0);
  int touchValue=digitalRead(TOUCH);
  delay(200);
  if(touchValue==HIGH)
  { 
    startTime=millis();
    
    while(digitalRead(TOUCH)==HIGH);
    touchTime=millis()-startTime;
    if(touchTime>=2000)
    {
      mp3_player.play(6);  //6
      display.setTextSize(2);
      Serial.println("holding");
      display.clearDisplay();
      display.println("Now put drug.");
      display.display();
      delay(1000); 

      data=drug_tyep+count;
      
      switch(data)
      {
        case 11: a_pump_loop(90); break;
        case 12: a_pump_loop(150); break;
        case 13: a_pump_loop(220); break;
        case 14: a_pump_loop(280); break;
        case 15: a_pump_loop(390); break;
        case 16: a_pump_loop(470); break;
    
        case 21: b_pump_loop(90); break;
        case 22: b_pump_loop(150); break;
        case 23: b_pump_loop(220); break;
        case 24: b_pump_loop(280); break;
        case 25: b_pump_loop(390); break;
        case 26: b_pump_loop(470); break;
      }
    }
    else
    {
      count++;
      if(count==10) count=1;
      Serial.print("Touched count: ");
      Serial.println(count);
      String str=String(count)+"mL";
      display.clearDisplay();
      display.setTextSize(3);
      display.println(str);
      display.display();
      speaker(count);
    }     
  }  
}


void speaker(int tabcount)
{
 switch(tabcount)
  {
    case 1:
      mp3_player.play(1);
      delay(1000);
      break;
    case 2:
      mp3_player.play(5);  //5
      delay(1000);
      break;
     case 3:
      mp3_player.play(4); //4
      delay(1000);
      break;   
     case 4:
      mp3_player.play(3); //3
      delay(1000);
      break;  
     case 5:
      mp3_player.play(2); //2
      delay(1000);
      break;    
     case 6:
      mp3_player.play(10);// 이제 약병에 담습니다.
      delay(1000);
      break; 
     case 7:
      mp3_player.play(9);  //9
      delay(1000);
      break; 
     case 8:
      mp3_player.play(8);
      delay(1000);
      break;
     case 9:
      mp3_player.play(7);  //7
      delay(1000);
      break;
  }
}

void a_pump_loop(int second)
{
  if (a_motorStatus == false)
  {
    a_motorStatus = true;

    digitalWrite(aMotor, HIGH);
    digitalWrite(bMotor, LOW);
    delay(second);

    digitalWrite(aMotor, LOW);
    digitalWrite(bMotor, LOW);

    a_motorStatus = false;
  }
}

void b_pump_loop(int second)
{
  if (b_motorStatus == false)
  {
    b_motorStatus = true;

    digitalWrite(cMotor, HIGH);
    digitalWrite(dMotor, LOW);
    delay(second);

    digitalWrite(cMotor, LOW);
    digitalWrite(dMotor, LOW);

    b_motorStatus = false;
  }
}
