#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define aMotor  5
#define bMotor  6
#define cMotor  12
#define dMotor  13
#define BUTTON  3
#define TOUCH 4

Adafruit_SSD1306 display(-1);

unsigned long prevSpeak=0;
boolean a_motorStatus = false;
boolean b_motorStatus = false;

int drugType=0;
int data=0;
int count=0;
String str;

SoftwareSerial mp3_serial(10,11);
unsigned long startTime;
unsigned long touchTime;


void speaker(int tabcount);

DFRobotDFPlayerMini mp3_player;

void setup()
{
 
  pinMode(aMotor, OUTPUT);
  pinMode(bMotor, OUTPUT);
  pinMode(cMotor, OUTPUT);
  pinMode(dMotor, OUTPUT);
  
  Serial.begin(9600);
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.println("Smart Drug");
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  
  mp3_serial.begin(9600);

  mp3_player.begin(mp3_serial);

  mp3_player.volume(20);  
  pinMode(TOUCH,INPUT);
}

void loop()
{ 
  display.setCursor(10,0);
  int touchValue=digitalRead(TOUCH);

  if(touchValue==HIGH)
  { 
    startTime=millis();
    
    while(digitalRead(TOUCH)==HIGH);
    touchTime=millis()-startTime;
    if(touchTime>=2000)
    {
      drugType++;
      if(drugType%2==0)
      {
        display.clearDisplay();
        display.setTextSize(3);
        display.println("1th drug");
        display.display();
        mp3_player.play(11);
      }
      else
      {
        display.clearDisplay();
        display.setTextSize(3);
        display.println("2th drug");
        display.display();
        mp3_player.play(10);
      }
      count=0;
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
  if(digitalRead(BUTTON)==HIGH)
  {
    if(drugType%2==0) data=count+10;
  
    else data=count+20;
    mp3_player.play(5);
    display.clearDisplay();
    display.setTextSize(3);
    display.println(data);
    display.display();

    switch(data)
      {
        case 11: a_pump_loop(90); break;
        case 12: a_pump_loop(150); break;
        case 13: a_pump_loop(220); break;
        case 14: a_pump_loop(280); break;
        case 15: a_pump_loop(390); break;
        case 16: a_pump_loop(470); break;
        case 17: a_pump_loop(570); break;
        case 18: a_pump_loop(650); break;
        case 19: a_pump_loop(750); break;
    
        case 21: b_pump_loop(90); break;
        case 22: b_pump_loop(150); break;
        case 23: b_pump_loop(220); break;
        case 24: b_pump_loop(280); break;
        case 25: b_pump_loop(390); break;
        case 26: b_pump_loop(470); break;
        case 27: b_pump_loop(570); break;
        case 28: b_pump_loop(650); break;
        case 29: b_pump_loop(750); break;
      } 
  }
}


void speaker(int tabcount)
{
 unsigned long currentTime=millis();
 if(currentTime-prevSpeak>1000)
 {
  prevSpeak=currentTime;
  switch(tabcount)
  {
    case 1:
      mp3_player.play(12); //5ml
      
      break;
    case 2:
      mp3_player.play(4);  //이제 약병에 담습니다.
      
      break;
     case 3:
      mp3_player.play(3); //2ml
      
      break;   
     case 4:
      mp3_player.play(2); //3mL
      
      break;  
     case 5:
      mp3_player.play(1); //4ml
      
      break;    
     case 6:
      mp3_player.play(9);// 두번째 물약입니다.
      
      break; 
     case 7:
      mp3_player.play(8);  //6ml
      
      break; 
     case 8:
      mp3_player.play(7); //7ml
      
      break;
     case 9:
      mp3_player.play(6);  //8ml
      
      break;
  }
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
