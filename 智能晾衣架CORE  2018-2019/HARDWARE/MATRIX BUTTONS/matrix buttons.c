#include "stm32w4k32s4.h"
#include "delay.h"
#include "matrix buttons.h"
#include "sys.h"

////////////////////ATTENTION///////////////////
//   本程序基于STM32W4K32S4-LQFP64S单片机
//   矩阵键盘的引脚为P60-P67
//   作者单位：北京理工大学珠海学院
////////////////////////////////////////////////
#define GPIO_KEY P6


////////////////////////////////////////////////////////	
//函数名:Press_Number
//函数作用：识别4X4矩阵按键被按下的键名，并返回对应值
//函数备注：	
////////////////////////////////////////////////////////
u8 Press_Number()
{
	u8 KeyValue;
  char a=0;
	char g=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		delay_10ms();//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{
			
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
			{
				delay_10ms();
				g++;
			}
		}
	}

	return KeyValue;
}

////////////////////////////////////////////////////////	
//函数名:martix_button_getchar4bit
//函数作用：利用矩阵键盘得到一个两位16进制数，返回对应数值
//函数备注：	
////////////////////////////////////////////////////////
//u16 martix_button_getchar8bit()
//{
//	u16 H4B,L4B;
//	u16 value;
//	
//	H4B = (Press_Number() << 4);
//	L4B = Press_Number();
//	value = H4B + L4B;
//	
//	return value;
//}











