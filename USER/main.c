#include "stdlib.h"
#include "stdio.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"   
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"
#include "w25qxx.h"   
#include "ff.h"
#include "exfuns.h"   
#include "text.h"
#include "piclib.h"	
#include "string.h"		
#include "math.h"
 
#include "servo.h"
#include "limit_switch.h"
#include "push.h"
#include "step_motor.h"
#include "beep.h"
#include "chaoshengbo.h"

void showPICTURE(int a);//图片显示函数

/************************************************
 ALIENTEK精英STM32开发板实验38
 图片显示 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


//得到path路径下,目标文件的总个数
//path:路径		    
//返回值:总有效文件数
u16 pic_get_tnum(u8 *path)
{	  
	u8 res;
	u16 rval=0;
 	DIR tdir;	 		//临时目录
	FILINFO tfileinfo;	//临时文件信息	
	u8 *fn;	 			 			   			     
    res=f_opendir(&tdir,(const TCHAR*)path); 	//打开目录
  	tfileinfo.lfsize=_MAX_LFN*2+1;				//长文件名最大长度
	tfileinfo.lfname=mymalloc(SRAMIN,tfileinfo.lfsize);//为长文件缓存区分配内存
	if(res==FR_OK&&tfileinfo.lfname!=NULL)
	{
		while(1)//查询总的有效文件数
		{
	        res=f_readdir(&tdir,&tfileinfo);       		//读取目录下的一个文件
	        if(res!=FR_OK||tfileinfo.fname[0]==0)break;	//错误了/到末尾了,退出		  
     		fn=(u8*)(*tfileinfo.lfname?tfileinfo.lfname:tfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//取高四位,看看是不是图片文件	
			{
				rval++;//有效文件数增加1
			}	    
		}  
	} 
	return rval;
}

///////////////////////////////////
	u8 res;
 	DIR picdir;	 		//图片目录
	FILINFO picfileinfo;//文件信息
	u8 *fn;   			//长文件名
	u8 *pname;			//带路径的文件名
	u16 totpicnum; 		//图片文件总数
	u16 curindex;		//图片当前索引
//u8 KEY;				//键值
//u8 pause=0;			//暂停标记
//u8 t;
	u16 temp;
	u16 *picindextbl;	//图片索引表 
//////////////////////////////////////


 int main(void)
 {	 
	 
	   
	    	vu8 key=0;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为115200
	 
	   // USART2_Init(4800);
	    //UART4_Init(9600);
	    exit_init();
	    Stmo_Init();
	    Servo_Init();
	    PUSH_Init();
		  step_motor_init();
		
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD   
  W25QXX_Init();				//初始化W25Q128
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
  POINT_COLOR=RED;      

/////////////////////////////////////////////////////
	while(font_init()) 		//检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
		delay_ms(200);				  
	}  	

//////////////////////////////////////////
 	Show_Str(30,50,200,16,"第七届工程能力综合能力训练大赛",16,0);				    	 
	Show_Str(30,70,200,16,"智能垃圾分类",16,0);				    	 
	Show_Str(30,90,200,16,"STM32F103系列",16,0);				    	 
	Show_Str(30,110,200,16,"正点原子开发",16,0);				    	 
	Show_Str(30,130,200,16,"",16,0);				    	 
	Show_Str(30,150,200,16,"2021年3月20日",16,0);
	
//////////////////////////////////////////////////	
	
//	while(f_opendir(&picdir,"0:/PICTURE"))//打开图片文件夹
//	{
//	Show_Str(30,170,240,16,"PICTURE文件夹错误!",16,0);
//	delay_ms(200);				  
//	LCD_Fill(30,170,240,186,WHITE);//清除显示	     
//	delay_ms(200);
//}  
////////////////////////////////////////////////////////	
	totpicnum=pic_get_tnum("0:/PICTURE"); //得到总有效文件数
///////////////////////////////////////////////////////////


	
  picfileinfo.lfsize=_MAX_LFN*2+1;						//长文件名最大长度
	picfileinfo.lfname=mymalloc(SRAMIN,picfileinfo.lfsize);	//为长文件缓存区分配内存
 	pname=mymalloc(SRAMIN,picfileinfo.lfsize);				//为带路径的文件名分配内存
 	picindextbl=mymalloc(SRAMIN,2*totpicnum);				//申请2*totpicnum个字节的内存,用于存放图片索引
	
	///////////////////////////////////////////////////////

	
	//记录索引
  res=f_opendir(&picdir,"0:/PICTURE"); //打开目录
	if(res==FR_OK)
	{
		curindex=0;//当前索引为0
		while(1)//全部查询一遍
		{
			temp=picdir.index;								//记录当前index
	    res=f_readdir(&picdir,&picfileinfo);       		//读取目录下的一个文件
	    if(res!=FR_OK||picfileinfo.fname[0]==0)break;	//错误了/到末尾了,退出		  
     	fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//取高四位,看看是不是图片文件	
			{
				picindextbl[curindex]=temp;//记录索引
				curindex++;
			}	    
		} 
	}  

/////////////////////////////////////////////////////

	
	Show_Str(30,170,240,16,"等待复位",16,0); 
	delay_ms(1500);
	piclib_init();										//初始化画图	   	   
  res=f_opendir(&picdir,(const TCHAR*)"0:/PICTURE"); 	//打开目录
	
//////////////////////////////////////////////////////////
     //showPICTURE(1);//播放宣传片	
		 //step_motor_init();//电机复位

	 while(res==FR_OK)//打开成功
	 {			 	
while(1)
{ 
			// printf("ok");
		  if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='2')
			{         //showPICTURE(1);
                // PUSH_True();
                //delay_s(6);
                //PUSH_False();
                //delay_s(6);
								printf("12");
                STEP_M(23,1);
                servo2_go(15);
                delay_ms(1500);
                servo2_go(48);
                delay_ms(1500);
                STEP_M(23,0);
	//
			}
		  else	if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='3')
			{         //showPICTURE(2);
				        printf("12");
                STEP_M(21,0);
                servo2_go(80);
                delay_ms(1500);
                servo2_go(48);
                STEP_M(21,1);

			}
			else	if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='4')
			{     //showPICTURE(3);	
            STEP_M(21,0);
            servo2_go(15);
            delay_ms(1500);
            servo2_go(48);
            STEP_M(21,1);
			}
			else	if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='5')
			{     //showPICTURE(4);	
            STEP_M(23,1);
            servo2_go(80);
            delay_ms(1500);
            servo2_go(48);
            STEP_M(23,0);

			}
			else	if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='6')
			{     //showPICTURE(5);	
				    STEP_M(23,1);
            servo2_go(80);
            delay_ms(1500);
            servo2_go(48);
            STEP_M(23,0);
			}
			else	if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='7')
			{        // showPICTURE(6);
                PUSH_True();
                delay_s(6);
                PUSH_False();
                delay_s(6);

                STEP_M(23,1);
                servo2_go(15);
                delay_ms(1500);
                servo2_go(48);
                delay_ms(1500);
                STEP_M(23,0);

			}
			else if(USART_RX_BUF[0]=='1'&&USART_RX_BUF[1]=='8')
			{
				       // showPICTURE(7);	
	     	        delay_ms(300);	 //延时300ms
	    	
			}
			USART_RX_BUF[0]='\0';
			USART_RX_STA=0;
		}					
			
 } 		

	 myfree(SRAMIN,picfileinfo.lfname);	//释放内存			    
	 myfree(SRAMIN,pname);				//释放内存			    
	 myfree(SRAMIN,picindextbl);			//释放内存		

}


void showPICTURE(int a)//图片显示函数
{
	  curindex=a;											//从3开始显示
		dir_sdi(&picdir,picindextbl[curindex]);			//改变当前目录索引	   
    res=f_readdir(&picdir,&picfileinfo);       		//读取目录下的一个文件
    fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
		strcpy((char*)pname,"0:/PICTURE/");				//复制路径(目录)
		strcat((char*)pname,(const char*)fn);  			//将文件名接在后面
 		LCD_Clear(BLACK);
 		ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,1);//显示图片    
		res=0; 
    delay_ms(20000);	
	
}






/*
KEY=KEY_Scan(0);		//扫描按键
			if(t>250)key=1;			//模拟一次按下KEY0    
			if((t%20)==0)LED0=!LED0;//LED0闪烁,提示程序正在运行.
			if(KEY==KEY1_PRES)		//上一张
			{
				if(curindex)curindex--;
				else curindex=totpicnum-1;
				break;
			}else if(KEY==KEY0_PRES)//下一张
			{
				curindex++;		   	
				if(curindex>=totpicnum)curindex=0;//到末尾的时候,自动从头开始
				break;
			}else if(KEY==WKUP_PRES)
			{
				pause=!pause;
				LED1=!pause; 	//暂停的时候LED1亮.  
			}
			if(pause==0)t++;
			delay_ms(10); 
*/

