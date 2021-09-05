#include "pid.h"
#include "iodefine.h"
#include <Arduino.h>

extern float rpmLeft; //link the left rpm from main;
extern float rpmRight; //link the right rpm from main;
extern float speedLeft; //link the left speed from main;
extern float speedRight; //link the left speed from main;
extern long interval;

//Set up 3 coeff for PID control;
float Kp, Ki, Kd;
float Kpp, Kii, Kdd;

float err_vleft, err_vright; //The difference between the left and right wheels speed and the theoretical value at the current time;

float err_vleft_pre, err_vright_pre; //The difference between the left and right wheels speed and the theoretical value at the previous time;

float proportionL; //PL
float integralL; //IL
float differentialL; //DL

float proportionR; //PR
float integralR; //IR
float differentialR; //DR

unsigned short pwm_left, pwm_right; //0~255

const float ideal_v = 1;

float odom_x;
float odom_y;
float odom_theta;

float v;
float w;
float d;
float Width = 0.155;


void setUpPID() //initialize PID coefficients and PWM of the two motors;
{
  Kp = 140.02;
  Ki = 12;
  Kd = 1.2;

  Kpp = 137.02;
  Kii = 12;
  Kdd = 1.2;

  pwm_left = 255 * 0.6;
  pwm_right = 255 * 0.6;

  odom_x = 0;
  odom_y = 0;
  odom_theta = 90*(PI/180);

  v = 0;
  w = 0;
  d = 0;

};



void updatePID() //update PID coeff;
{
  //比例项
  err_vleft = speedLeft - ideal_v;
  err_vright = speedRight - ideal_v;
  proportionL = Kp * err_vleft;
  proportionR = Kpp * err_vright;
  //积分项
  integralL += Ki * err_vleft;
  integralR += Kii * err_vright;
  //微分项
  differentialL = Kd * (err_vleft - err_vleft_pre);
  differentialR = Kdd * (err_vright - err_vright_pre);

  //Adjustment;
  pwm_left = proportionL + integralL + differentialL;//need to be mapped to 0-255
  pwm_right = proportionR + integralR + differentialR;//need to be mapped to 0-255

  constrain(pwm_left, 0, 200);
  constrain(pwm_right, 0, 200);

  //Update the error;
  err_vleft_pre = err_vleft;
  err_vright_pre = err_vright;
  //The right wheel has the same speed as the left wheel
};

void speedMeasure()
{
  v = (speedLeft + speedRight) / 2; //Linear speed;
  w = (speedRight - speedLeft) / Width; //Angular velocity;
  d = v * interval / 1000;

  odom_x += d * cos(odom_theta + w * 0.5 * interval / (1000));
  odom_y += d * sin(odom_theta + w * 0.5 * interval / (1000));
  odom_theta += w * (interval / 1000);
};

void printOdom()
{
  Serial.print(odom_x);
  Serial.print('\t');
  Serial.print(odom_y);
  Serial.print('\t');
  Serial.println(odom_theta);
};

void printSpeed()
{
  Serial.print(speedLeft);
  Serial.print('\t');
  Serial.print(speedRight);
  Serial.print('\t');
  Serial.println(1);
};
