#include <SoftwareSerial.h>

#define BTtx  2
#define BTrx  3
#define aMotor  10
#define bMotor  6

SoftwareSerial BT(BTtx, BTrx);

char power;

void setup()
{
	Serial.begin(9600);
	BT.begin(9600);
	pinMode(aMotor, OUTPUT);
	pinMode(bMotor, OUTPUT);
}

void loop()
{
	if (Serial.available() > 0)
	{
		power =Serial.read();
	}

	switch (power)
	{
	case '1':
		pump(100);
		break;
	case '2':
		pump(200);
		break;
	case '3':
		pump(300);
		break;
	}

	power = '0';
	
}



void pump(int power)
{
	Serial.println("Start\n");
	digitalWrite(aMotor, HIGH);
	digitalWrite(bMotor, LOW);
	delay(power);
	digitalWrite(aMotor, LOW);
	digitalWrite(bMotor, LOW);
	Serial.println("end\n");
}
