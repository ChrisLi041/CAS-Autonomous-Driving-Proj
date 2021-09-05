//#include "MPU9250.h"
#include "irsensor.h"
#include <Arduino.h>
#include "motor.h"
#include "iodefine.h"
#include "encoder.h"
#include "pid.h"
#include "gps.h"
#include <SoftwareSerial.h> //enable 

SoftwareSerial mySerial(13, 4); // RX, TX
//MPU9250 mpu;


byte buf[4];
float angle;
float lastAngle = 0;

String name = "";
long interval = 0;
long previousMillis = 0;
long currentMillis = 0;
long numPulseLeft = 0;
long numPulseRight = 0;
float rpmLeft = 0;
float rpmRight = 0;
float speedLeft = 0;
float speedRight = 0;
extern long ticks_left_encoder;
extern long ticks_right_encoder;//Motor + when rotating CW, - when CCW.
extern long old_left_encoder;
extern long old_right_encoder;
extern unsigned short pwm_left, pwm_right; //link the pwm;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  //设置控制电机的IO口
  //IN1,IN2,IN3,IN4接到了电机驱动板上
  //设置IN1~IN4为输出引脚
  //pinMode()
  setupMotor();
  setupEncoder();
  Serial.println("Enter your command.");
  previousMillis = millis();
  setUpPID(); //initialize PID coefficients and PWM of the two motors;

  setupIrSensor();

//    Wire.begin();
//
//    delay(2000);
//    mpu.setup();
//
//    delay(5000);
//
//    // calibrate anytime you want to
//    mpu.calibrateAccelGyro();
//    mpu.calibrateMag();
//
//    mpu.printCalibration();
}

//void loop()
//{
//  //anaReadIrSensor();
//  readIR();
//}


//等价于while(true)
void loop()
{
  readIR();
  
if (mySerial.available() > 0) {
    size_t data = mySerial.readBytesUntil('\n',buf,100);
    Serial.print("Turning Angle: ");
    memcpy(&angle,buf,4);
    Serial.println(angle);
    memset(buf, 0, sizeof(buf));
    if(angle == 10) //turnleft;
    {
      Serial.println("LEFT");
      turnLeft();
      lastAngle = angle;
      Serial.flush();
    }
    else if(angle == -10) //turnright;
    {
      Serial.println("RIGHT");
      turnRight();
      lastAngle = angle;
      Serial.flush();
    }
    else if (angle == 99) //cannot find path;
    { 
      Serial.println("CANNOT FIND PATH");
      if (lastAngle == -10) //turn right;
      {
        Serial.println("TURN BIG RIGHT");
         findPathCW();
         lastAngle = angle;
      }
      else if (lastAngle == 10) //turn left;
      {
//        Serial.println(angle);
//        Serial.println(lastAngle);
         Serial.println("TURN BIG LEFT");
         findPathCCW();
         lastAngle = angle;
      }
      else if (lastAngle == 0) //straight;
      {
        Serial.println("TOO FAST GO BACK");
        backward();
        lastAngle = angle;
      }
      else //looking;
      {
//        int flag =  random(2);
//        Serial.println("DONT SEE ANYTHING");
//        if (flag = 0)
//        {
//          findPathCCW();
//        }
//        else
//        {
//          findPathCW();
//        }
        backward();
        lastAngle = angle;
      }
      Serial.flush();
    }
    else
    {
      Serial.println("FORWARD");
      forward();
      Serial.flush();
    }
   //Serial.print(Serial.read(),HEX);
   //delay(500);
   //Serial.println(sizeof(float));
  }

//  while (Serial.available() == 0) //prompt user to enter a command;
//  {
    
//    delay(50);
//    currentMillis = millis(); //record the current time;
//    interval = currentMillis - previousMillis; //record the interval between two time stamps;
//    previousMillis = currentMillis; //update previous time;
//    numPulseLeft = ticks_left_encoder - old_left_encoder;
//    numPulseRight = ticks_right_encoder - old_right_encoder;
//    old_left_encoder = ticks_left_encoder;
//    old_right_encoder = ticks_right_encoder;
//    rpmLeft = (float)60 * (1000*numPulseLeft / (interval)) / (390);
//    rpmRight = (float)60 * (1000*numPulseRight / (interval)) / (390);
//    speedLeft = PI * 0.0637 * rpmLeft / 60;
//    speedRight = PI * 0.0637 * rpmRight / 60;
//    //Print the speed of wheels;
//    speedMeasure();
//    //PID
//    updatePID(); //update PID coeff;
//    //      printEncoder();
//    printOdom();
//    
//    printSpeed();
//    Serial.println("--- ---- ---- ---- ---");
//    name = Serial.readString();
//    
//
//    if (name == "w")
//    {
//      forward();
//      Serial.println(name);
//    }
//    if (name == "a")
//    {
//      turnLeft();
//    }
//    if (name == "s")
//    {
//      moveStop();
//    }
//    if (name == "d")
//    {
//      turnRight();
//    }
//    if (name == "x")
//    {
//      backward();
//    }
  //}

}
