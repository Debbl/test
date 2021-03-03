#include "servo.h"
#include "delay.h"

void servo1(u8 angle)
{
    u16 time;
    time=8774-angle/0.2;
    TIM_SetCompare1(TIM3,time);
}

void servo2(u8 angle)
{
    u16 time;
    time=8774-angle/0.2;
    TIM_SetCompare2(TIM3,time);
}

void servo2_go(u8 angle)
{
    u8 i;
    u16 time;
    for(i=0; i<=angle; i++)
    {
        time=8774-i/0.2;
        TIM_SetCompare2(TIM3,time);
        delay_ms(1);
    }
}

void servo1_go(u8 angle)
{
    u8 i;
    u16 time;
    for(i=0; i<=angle; i++)
    {
        time=8774-i/0.2;
        TIM_SetCompare1(TIM3,time);
        delay_ms(1);
    }

}


void Servo_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;  					 /*IO初始化结构体*/

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   		 /*定时器初始化结构体*/

    TIM_OCInitTypeDef TIM_OCInitStruct;              		 /*初始化输出比较参数结构体*/

    RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE ) ;  /*定时器时钟使能*/
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE );  /*IO使能*/

    GPIO_InitStruct.GPIO_Pin   =  GPIO_Pin_7|GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);                       /*IO初始化*/

    TIM_TimeBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1;     //时钟分割
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_TimeBaseInitStruct.TIM_Period =8999;                    //定时器周期
    TIM_TimeBaseInitStruct.TIM_Prescaler = 159;                   //预分频器
    TIM_TimeBaseInit (TIM3, &TIM_TimeBaseInitStruct);       	 /*定时器初始化*/

    //初始化 TIM3 Channel_2 PWM 模式

    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //空闲状态下比较输出状态
    TIM_OCInitStruct.TIM_OCMode =TIM_OCMode_PWM2;            //比较输出模式
    TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;    //输出极性
    TIM_OC2Init (TIM3, &TIM_OCInitStruct);                   //初始化输出比较参数
    TIM_OC2PreloadConfig  (TIM3,TIM_OCPreload_Enable);

    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //空闲状态下比较输出状态
    TIM_OCInitStruct.TIM_OCMode =TIM_OCMode_PWM2;            //比较输出模式
    TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;    //输出极性
    TIM_OC1Init (TIM3, &TIM_OCInitStruct);                   //初始化输出比较参数
    TIM_OC1PreloadConfig  (TIM3,TIM_OCPreload_Enable);

    TIM_Cmd (TIM3,ENABLE );

}
