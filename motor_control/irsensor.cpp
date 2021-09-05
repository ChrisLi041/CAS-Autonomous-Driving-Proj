#include "irsensor.h"

unsigned char ir_state;
unsigned char ir_in1,ir_in2,ir_in3,ir_in4,ir_in5;

extern unsigned int pwm_l, pwm_r;//in motor.cpp

//Define the variables of the data collected by each tracking infrared pin
int P1;
int P2;
int P3;
int P4;
int P5;

void setupIrSensor()
{
	pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
	pinMode(IR3, INPUT);
	pinMode(IR4, INPUT);
	pinMode(IR5, INPUT);

  delay(10);
  
//  The four-way tracking infrared sensor is initialized to high voltage
  digitalWrite(IR1, HIGH);
  digitalWrite(IR2, HIGH);
  digitalWrite(IR3, HIGH);
  digitalWrite(IR4, HIGH);
  digitalWrite(IR5, HIGH);
}

// If the IR sensor is connected to the analog pin, use this function
void anaReadIrSensor()
{
	ir_in1 = mappingAnalog(IR1);
	ir_in2 = mappingAnalog(IR2);
	ir_in3 = mappingAnalog(IR3);
	ir_in4 = mappingAnalog(IR4);
	ir_in5 = mappingAnalog(IR5);
	ir_state = 0;
	ir_state = ir_in1<<4 | ir_in2<<3 | ir_in3<<2 | ir_in4<<1 | ir_in5;
	Serial.println(ir_state,BIN);//for debug
}

unsigned char mappingAnalog(int pin)
{
  if(analogRead(pin)>900)
    return 1;
  else
    return 0;
}

// If the IR sensor is connected to the digital pin directly, use this function
//void digReadIrSensor()
//{
//	ir_in1 = digitalRead(IR1);
//	ir_in2 = digitalRead(IR2);
//	ir_in3 = digitalRead(IR3);
//	ir_in4 = digitalRead(IR4);
//	ir_in5 = digitalRead(IR5);
//	ir_state = 0;
//	ir_state = ir_in1<<4 | ir_in2<<3 | ir_in3<<2 | ir_in4<<1 | ir_in5;
//	Serial.println(ir_state,BIN);//for debug
//}


//void irTracking()
//{
//	anaReadIrSensor();
//	if(ir_in1==0 && ir_in2==1 && ir_in3==1 && ir_in4==1 && ir_in5==0)
//	{
//		updatePid();
//		forward(pwm_l,pwm_r);
//	}
//	else if((ir_in1==0 && ir_in2==0 && ir_in4==1) || (ir_in1==0 && ir_in2==0 && ir_in3==0 && ir_in4==0 && ir_in5==1))
//	{
//		spinRight(80,0);
//	}
//	else if((ir_in2==1 && ir_in4==0 && ir_in5==0) || (ir_in1==1 && ir_in2==0 && ir_in3==0 && ir_in4==0 && ir_in5==0))
//	{
//		spinLeft(0,80);
//		
//	}
//	else if(ir_state==0 || ir_state==0x1F)//not on the position
//	{
//		randMove(); //Random movement to find the color code, need field test to modify
//	}
//	else
//	{
//		Serial.println("unknown state!");//The state may be incomplete and needs to be debugged
//	}
//}


//How to randomly move so that the robot can find the color mark most quickly requires on-site debugging
//void randMove()
//{
//	while(ir_state==0 || ir_state==0x1F)
//	{
//		forward(pwm_l,pwm_r);
//		delay(100);
//		left(0,80);
//		delay(10);
//		forward(pwm_l,pwm_r);
//		delay(100);
//		left(0,80);
//		delay(10);
//		forward(pwm_l,pwm_r);
//		delay(100);
//		left(0,80);
//		delay(10);
//		forward(pwm_l,pwm_r);
//		delay(100);
//	}
//}




//void setupIR()
//{

//	pinMode(TrackSensorLeftPin1, INPUT);
//	pinMode(TrackSensorLeftPin2, INPUT);
//	pinMode(TrackSensorRightPin1, INPUT);
//	pinMode(TrackSensorRightPin2, INPUT);
//	
//	delay(10);
//	

//	digitalWrite(TrackSensorLeftPin1, HIGH);
//	digitalWrite(TrackSensorLeftPin2, HIGH);
//	digitalWrite(TrackSensorRightPin1, HIGH);
//	digitalWrite(TrackSensorRightPin2, HIGH);
//
//}


void readIR()
{
	//When the black line is detected, the corresponding indicator light of the tracking module is on, and the port level is LOW
  //When the black line is not detected, the corresponding indicator light of the tracking module is off, and the port level is HIGH
	P1  = digitalRead(IR1);
	P2  = digitalRead(IR2);
	P4  = digitalRead(IR3);
	P4  = digitalRead(IR4);
  P5  = digitalRead(IR5);
	
	/*
	Serial.print(TrackSensorLeftValue1);
	Serial.print('\t');
	Serial.print(TrackSensorLeftValue2);
	Serial.print('\t');
	Serial.print(TrackSensorRightValue1);
	Serial.print('\t');
	Serial.println(TrackSensorRightValue2);
	*/
	
}


//void Tracking()
//{
//	readIR();
//
//	//Four-way tracking pin level status
//	// 0 0 X 0
//	// 1 0 X 0
//	// 0 1 X 0
//	//When the above 6 levels are in the state, the trolley turns right on the spot, the speed is 250, and the delay is 80ms
//	//Handle the rotation of acute angles
//	if ( (TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) &&  TrackSensorRightValue2 == LOW)
//	{
//		spinRight(120, 120);
//		delay(80);
//	}
//	//Four-way tracking pin level status
//	// 0 X 0 0       
//	// 0 X 0 1 
//	// 0 X 1 0       

//	else if ( TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW ||  TrackSensorRightValue2 == LOW))
//	{
//		spinLeft(120, 120);
//		delay(80);
//	}
//	// 0 X X X
//	//left most
//	else if ( TrackSensorLeftValue1 == LOW)
//	{
//		spinLeft(100, 100);
//	//delay(2);
//	}
//	// X X X 0
//	//right most
//	else if ( TrackSensorRightValue2 == LOW )
//	{
//		spinRight(100, 100);
//		//delay(2);
//	}
//	//Four-way tracking pin level status
//	// X 0 1 X
//	//Left turn (acute)
//	else if ( TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
//	{
//		left(0, 120);
//	}
//	//Four-way tracking pin level status
//	// X 1 0 X  
//	//Right turn (acute)
//	else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
//	{
//		right(120, 0);
//	}
//	//Four-way tracking pin level status
//	// X 0 0 X
//	//straight line
//	else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
//	{
//		forward(120, 120);
//	}
//	//1 1 1 1, remain status
//}
