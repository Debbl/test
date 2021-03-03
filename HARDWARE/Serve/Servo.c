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
    GPIO_InitTypeDef  GPIO_InitStruct;  					 /*IO��ʼ���ṹ��*/

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   		 /*��ʱ����ʼ���ṹ��*/

    TIM_OCInitTypeDef TIM_OCInitStruct;              		 /*��ʼ������Ƚϲ����ṹ��*/

    RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE ) ;  /*��ʱ��ʱ��ʹ��*/
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE );  /*IOʹ��*/

    GPIO_InitStruct.GPIO_Pin   =  GPIO_Pin_7|GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);                       /*IO��ʼ��*/

    TIM_TimeBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1;     //ʱ�ӷָ�
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //����ģʽ
    TIM_TimeBaseInitStruct.TIM_Period =8999;                    //��ʱ������
    TIM_TimeBaseInitStruct.TIM_Prescaler = 159;                   //Ԥ��Ƶ��
    TIM_TimeBaseInit (TIM3, &TIM_TimeBaseInitStruct);       	 /*��ʱ����ʼ��*/

    //��ʼ�� TIM3 Channel_2 PWM ģʽ

    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //����״̬�±Ƚ����״̬
    TIM_OCInitStruct.TIM_OCMode =TIM_OCMode_PWM2;            //�Ƚ����ģʽ
    TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;    //�������
    TIM_OC2Init (TIM3, &TIM_OCInitStruct);                   //��ʼ������Ƚϲ���
    TIM_OC2PreloadConfig  (TIM3,TIM_OCPreload_Enable);

    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //����״̬�±Ƚ����״̬
    TIM_OCInitStruct.TIM_OCMode =TIM_OCMode_PWM2;            //�Ƚ����ģʽ
    TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;    //�������
    TIM_OC1Init (TIM3, &TIM_OCInitStruct);                   //��ʼ������Ƚϲ���
    TIM_OC1PreloadConfig  (TIM3,TIM_OCPreload_Enable);

    TIM_Cmd (TIM3,ENABLE );

}
