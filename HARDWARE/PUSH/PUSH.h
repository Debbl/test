#ifndef __PUSH_H
#define __PUSH_H
#include "sys.h"
#include "delay.h"

#define TUI1Q PGout(13)
#define TUI1H PGout(14)

#define TUI2Q PBout(8)
#define TUI2H PBout(9)

void PUSH_Init(void);
void PUSH_True(void);
void PUSH_False(void);




#endif
