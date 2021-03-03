#ifndef _CS_H
#define _CS_H

#include "sys.h"
#define uint unsigned int
#define TRIG_Send  PEout(1)
#define ECHO_Reci  PEin(2)

void CH_SR04_Init(void);
float Senor_Using(void);
void NVIC_Config(void);
#endif

