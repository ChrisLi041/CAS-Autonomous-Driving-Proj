#include "encoder.h"
#include "iodefine.h"
#include <Arduino.h>

long ticks_left_encoder = 0;
long ticks_right_encoder = 0;
long old_left_encoder = 0;
long old_right_encoder = 0;

//1. Encoder IO Setup，A and B as input；2. Cut-off settings
void setupEncoder()
{
	Serial.begin(9600);//Initialize Arrduino serial port as 9600
	
	pinMode(LA,INPUT);
	pinMode(LB,INPUT);
	pinMode(RA,INPUT);
	pinMode(RB,INPUT);
	
	attachInterrupt(0,updateLeftEncoder,RISING);//L encoder
	attachInterrupt(1,updateRightEncoder,RISING);//Right encoder
}


//Read the B signal level value at the rising edge of the left encoder A signal; count pulses
void updateLeftEncoder()
{
	int LBpin = digitalRead (LB);
  if (LBpin > 0)
  {
    ticks_left_encoder += 1;
  }
  else
  {
    ticks_left_encoder -= 1;
  }
}


void updateRightEncoder()
{
	int RBpin = digitalRead (RB);
  if (RBpin > 0)
  {
    ticks_right_encoder -= 1;
  }
  else
  {
    ticks_right_encoder += 1;
  }
}


//Serial port: print the pulse count value of the left and right encoders
void printEncoder()
{
	Serial.print(ticks_left_encoder);
	Serial.print('\t');
	Serial.println(ticks_right_encoder);
}
