#include "step_motor.h"
#include "limit_switch.h"
#include "servo.h"
#include "push.h"
#include "delay.h"
extern u8 dir_flag;
void Stmo_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    DI=0;
    PU=0;
}


/*l=1 顺时针转
  l=0 逆时针转*/
void STEP_M(u32 nloop,u8 l)
{
    u32 i;
    if(l==1)
    {
        DI=1;
        for (i = 0; i < nloop*1600; i++)
        {
            if(dir_flag==2)
            {
                EXTI->IMR&=~(EXTI_Line3);
                STEP_M(1,0);
                dir_flag=5;
                break;
            }

            PU=1;
            delay_us(100);
            PU=0;
            delay_us(100);
        }
    }
    else if(l==0)
    {
        DI=0;
        for (i = 0; i < nloop*1600; i++)
        {
            if(dir_flag==1)
            {
                EXTI->IMR&=~(EXTI_Line2);
                STEP_M(1,1);
                dir_flag=5;
                break;
            }
            PU=1;
            delay_us(100);
            PU=0;
            delay_us(100);
        }
    }
}

void step_motor_init(void)
{
    PUSH_False();
    delay_s(6);
    servo2_go(48);
    if(dir_flag==1)
    {
        EXTI->IMR&=~EXTI_Line2;
        EXTI->IMR&=~EXTI_Line3;
        STEP_M(31,1);
    }
    else if(limit_switch_Beh==0)
    {
        EXTI->IMR&=~EXTI_Line2;
        EXTI->IMR&=~EXTI_Line3;
        STEP_M(31,0);
    }
    else
    {
        STEP_M(80,1);
        STEP_M(31,0);
    }


}
