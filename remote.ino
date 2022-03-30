#include <IRremote.h>

#define RED 2
#define GREEN 3
#define BLUE  4

IRrecv irrecv(12);

decode_results results;

void setup()
{
  irrecv.enableIRIn();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  if(irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    if(results.value==0xFD30CF)
    {
      pump(90,1);
    }
    else if(results.value==0xFD08F7)
    {
      pump(150,2);
    }
    else if(results.value==0xFD08F7)
    {
      pump(150,3);
    }
    else if(results.value==0xFD08F7)
    {
      pump(280,4);
    }
    else if(results.value==0xFD08F7)
    {
      pump(300,5);
    }
    else if(results.value==0xFD08F7)
    {
      pump(350,6);
    }
    

    irrecv.resume();
    delay(50);
  }
}


void pump(int second, int count)
{
  display.clearDisplay();
  display.setTextSize(3);
  display.println(str);
  display.display();
  speaker(count);
  
  if (motorStatus == false)
  {
    motorStatus = true;

    digitalWrite(aMotor, HIGH);
    digitalWrite(bMotor, LOW);
    delay(second);

    digitalWrite(aMotor, LOW);
    digitalWrite(bMotor, LOW);

    motorStatus = false;
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
