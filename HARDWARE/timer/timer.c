#include "timer.h"
#include "voice.h"
#include "hc_sr04.h"
#include "oled.h"
float length1,length2,length3,length4;
extern uint8_t khsljtjm[];
extern uint8_t qjsql[];
extern const uint8_t dat5[];//垃圾满
extern const uint8_t dat6[];

void timer_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //使能对应RCC时钟

    TIM_TimeBaseInitStruct.TIM_Period=36000;
    TIM_TimeBaseInitStruct.TIM_Prescaler=8000;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);   //清除更新中断，免得一打开中断立即产生中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //打开定时器更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //选择串口1中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //抢占式中断优先级设置为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //响应式中断优先级设置为1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //使能中断
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
    {
//        length1 = Hcsr04GetLength1();
        length2=0;
        length2 = Hcsr04GetLength2();
//        length3 = Hcsr04GetLength3();
//        length4 = Hcsr04GetLength4();
        if(length2<30.0)              //||(length2<15.00)||(length3<15.00)||(length4<15.00))
        {
            OLED_Fill(0x00);
            OLED_showCHines(0,0,khsljtjm,7);
            OLED_showCHines(0,4,qjsql,4);
//            Voice_Cmd(point_song, 2, dat6);
        }
        else
            OLED_Fill(0x00);



        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志
    }

	}