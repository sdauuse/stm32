#include "stm32w4k32s4.h"
#include "sys.h"
#include "TAHS.h"
#include "oled.h"
#include "PWM.h"
#include "matrix buttons.h"
#include "delay.h"
#include "RUN.h"
#include "rain.h"




void main()
{
 	TAHSInit();   //温湿度传感器初始化    
	OLED_Init();  //oled初始化
	motorInit();  //电机初始化
	RainInit();   //雨滴传感器初始化
	P6=0x00;
	
	
	
	while(1)
	{	
		page1();   
		RUN();          //操作界面
	}
}














