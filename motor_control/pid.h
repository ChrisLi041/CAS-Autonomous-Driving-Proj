#ifndef _PID_H_
#define _PID_H_


void setUpPID(); //initialize PID coefficients and PWM of the two motors;
void updatePID(); //update PID coeff;
void speedMeasure();
void printSpeed();
void printOdom();

#endif
