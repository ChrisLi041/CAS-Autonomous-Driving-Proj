#ifndef _IRSENSOR_h_
#define _IRSENSOR_h_

#include <Arduino.h>
#include "iodefine.h"
#include "motor.h"
#include "pid.h"

void setupIrSensor();
void irTracking();
void randMove();
unsigned char mappingAnalog(int pin);
void digReadIrSensor();
void anaReadIrSensor();

void setupIR();
void readIR();
void Tracking();

#endif
