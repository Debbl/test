#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H
#include "sys.h"
#include "delay.h"

#define DI PGout(11)//DIR1
#define PU PGout(13)//PUL1

void Stmo_Init(void);
void STEP_M(u32 nloop,u8 l);

void step_motor_init(void);

#endif
