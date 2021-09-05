/*---------------------
*----------------------
*    Motor controller
*---------------------*/
#include "motor.h"
#include "iodefine.h"

extern unsigned short pwm_left,pwm_right;//link the pwm;

//Set the input and output mode of the motor-related pins
//pinMode()
void setupMotor()
{
	pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
	//ENB,IN1,IN2,IN3,IN4 output
	
}

//Forward
//The left and right motors rotate CW
//ENA，ENB----PWM > 0
//IN1,IN2: one close, the other open
//IN3,IN4: one close, the other open
//digitalWrite()
void forward()
{
	//L Motor
	analogWrite(ENA,65);//PWM pwm_left
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);

  //R Motor
  analogWrite(ENB,65);//PWM pwm_right
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);

  
}


//Backup
//The left and right motors rotate CCW
//ENA，ENB----PWM > 0
//IN1,IN2: one close, the other open (OPPOSITE TO FORWARD)
//IN3,IN4: one close, the other open (OPPOSITE TO FORWARD)
void backward()
{
	//L Motor
  analogWrite(ENA,65);//PWM
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);

  //R Motor
  analogWrite(ENB,65);//PWM
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}


//Stop
//The first method: ENA, ENB set to is 0
//The second method: set IN1 and IN2 to be open at the same time, the same is true for IN3 and IN4
void moveStop()
{
	//L Motor
  analogWrite(ENA,0);//PWM
  //R Motor
  analogWrite(ENB,0);//PWM
}


//Turn left
//Set the PWM value of the left motor to be less than the right motor
void turnLeft()
{
	//L Motor
  analogWrite(ENB,35);//PWM
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  //R Motor
  analogWrite(ENA,70);//PWM
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
}

//Turn right
//Set the PWM value of the right motor to be less than the left motor
void turnRight()
{
	//L Motor
  analogWrite(ENB,70);//PWM
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  //R Motor
  analogWrite(ENA,35);//PWM
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
}

//when the robot cannot find the lane around it:
void findPathCCW()
{
  //L Motor
  analogWrite(ENB,35);//PWM
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  
  //R Motor
  analogWrite(ENA,70);//PWM
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
}

void findPathCW()
{
  //L Motor
  analogWrite(ENB,70);//PWM
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  
  //R Motor
  analogWrite(ENA,35);//PWM
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,HIGH);
}
