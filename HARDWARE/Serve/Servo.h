#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f10x.h"

void Servo_Init(void);
void servo1_go(u8 angle);
void servo2_go(u8 angle);
#endif

