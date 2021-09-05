#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <Arduino.h>
void setupMotor();
void forward();
void backward();
void moveStop();
void turnLeft();
void turnRight();
void findPathCW();
void findPathCCW();


#endif
