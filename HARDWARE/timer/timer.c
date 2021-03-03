#include "timer.h"
#include "voice.h"
#include "hc_sr04.h"
#include "oled.h"
float length1,length2,length3,length4;
extern uint8_t khsljtjm[];
extern uint8_t qjsql[];
extern const uint8_t dat5[];//������
extern const uint8_t dat6[];

void timer_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //ʹ�ܶ�ӦRCCʱ��

    TIM_TimeBaseInitStruct.TIM_Period=36000;
    TIM_TimeBaseInitStruct.TIM_Prescaler=8000;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);   //��������жϣ����һ���ж����������ж�
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //ѡ�񴮿�1�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռʽ�ж����ȼ�����Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //��Ӧʽ�ж����ȼ�����Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
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



        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־
    }

	}