#include <SoftwareSerial.h>

#define aMotor  5
#define bMotor  6
#define BTtx	7
#define BTrx	8

boolean motorStatus = false;

SoftwareSerial BT(BTtx, BTrx);

void setup()
{
	BT.begin(9600);
	Serial.begin(9600);
	pinMode(aMotor, OUTPUT);
	pinMode(bMotor, OUTPUT);
	Serial.println("start\n");
}

void loop()
{
	if (BT.available() > 0)
	{
		byte data = BT.read();

		if (data == 1)
		{
			pump(90);
			Serial.println("100ml");
		}

		else if (data == 2)
		{
			pump(150);
			Serial.println("200ml");
		}

		else if (data == 3)
		{
			pump(220);
			Serial.println("300ml");
		}

		else if (data == 4)
		{
			pump(280);
			Serial.println("400ml");
		}

		else if (data == 5)
		{
			pump(390);           
			Serial.println("500ml");
		}

		else if (data == 6)
		{
			pump(470);
			Serial.println("600ml");
		}

		else if (data == 7)
		{
			pump(570);
			Serial.println("600ml");
		}

		else if (data == 8)
		{
			pump(650);
			Serial.println("600ml");
		}

		else if (data == 9)
		{
			pump(750);
			Serial.println("600ml");
		}
		
		data = 0;
		delay(1000);
	}
}


void pump(int second)
{
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
