#include "push.h"
#include "stm32f10x.h"

void PUSH_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
	

    TUI1Q=0;
    TUI1H=0;
    TUI2Q=0;
    TUI2H=0;
}
void PUSH_True(void)
{
    TUI1Q=1;
    TUI1H=0;
    TUI2Q=1;
    TUI2H=0;
}

void PUSH_False(void)
{
    TUI1Q=0;
    TUI1H=1;
    TUI2Q=0;
    TUI2H=1;
}
