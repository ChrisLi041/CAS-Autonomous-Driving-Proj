#ifndef _ENCODER_H_
#define _ENCODER_H_


void setupEncoder();//1. Encoder IO setting: set A phase and B phase as input mode; 2. Cut-off setting
void updateLeftEncoder();//Read the B signal level value at the rising edge of the left encoder A signal; count the pulses
void updateRightEncoder();
void printEncoder();//Serial port: print the pulse count value of the left and right encoders


#endif
