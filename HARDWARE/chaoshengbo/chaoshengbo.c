#include "chaoshengbo.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"


int overcount=0;


void NVIC_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructer;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
NVIC_InitStructer.NVIC_IRQChannel=TIM2_IRQn;
NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;

NVIC_Init(&NVIC_InitStructer);
}

void CH_SR04_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructer;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;

RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//TRIG/
GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStructer.GPIO_Pin=GPIO_Pin_1;
GPIO_Init(GPIOE, &GPIO_InitStructer);

//ECOH/
GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
GPIO_InitStructer.GPIO_Pin=GPIO_Pin_2;
GPIO_Init(GPIOE, &GPIO_InitStructer);


TIM_DeInit(TIM2);
TIM_TimeBaseInitStructer.TIM_Period=999;
TIM_TimeBaseInitStructer.TIM_Prescaler=71; 
TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructer);

TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
NVIC_Config();
TIM_Cmd(TIM2,DISABLE);

}



float Senor_Using(void)
{
float length=0,sum=0;
u16 tim;
int i=0;

while(i!=5)
{
PEout(1)=1;  
delay_us(20);  
PEout(1)=0;

while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==RESET);
TIM_Cmd(TIM2,ENABLE);

i+=1; 
while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==SET);
TIM_Cmd(TIM2,DISABLE);

tim=TIM_GetCounter(TIM2);

length=(tim+overcount*1000)/58.0;

sum=length+sum;
TIM2->CNT=0;  
overcount=0;  
delay_ms(100);
}
length=sum/5;
return length;
}



void TIM2_IRQHandler(void) 
{
if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
  {
TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
overcount++;

  }
}

