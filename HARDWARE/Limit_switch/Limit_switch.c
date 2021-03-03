#include "limit_switch.h"
u8 dir_flag=5;


void limit_switch_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，未按下按键时输入为1
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void exit_init(void)
{

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    limit_switch_gpio_init();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line=EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line=EXTI_Line3;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_Init(&EXTI_InitStructure);



    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
    {
        if(limit_switch_Fro==0)
            dir_flag=1;
    }
    EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE3上的中断标志位
}

void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        if(limit_switch_Beh==0)
            dir_flag=2;
    }
    EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE4上的中断标志位
}

