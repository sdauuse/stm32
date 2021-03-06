#include "stm32w4k32s4.h"
#include "oled.h"
#include "matrix buttons.h"
#include "RUN.h"
#include "delay.h"
#include "PWM.h"
#include "TAHS.h"
#include "sys.h"


////////////////////ATTENTION///////////////////
//   本程序基于STM32W4K32S4-LQFP64S单片机
//   
//   页面驱动功能文件
//   作者单位：北京理工大学珠海学院
////////////////////////////////////////////////
u8 num;

void RUN()
{
	do
	{
	//显示主页
	//“智能晾衣架�
	//按3,A继续
		OLED_ShowCHinese(16,2,0);
		OLED_ShowCHinese(32,2,1);
		OLED_ShowCHinese(48,2,2);
		OLED_ShowCHinese(64,2,3);
		OLED_ShowCHinese(80,2,4);
		
		OLED_ShowCHinese(24,6,10);
		OLED_ShowNum(40,6,3,1,16);
		OLED_ShowString(48,6,",");
		OLED_ShowChar(56,6,'A');
		OLED_ShowCHinese(64,6,5);
		OLED_ShowCHinese(80,6,6);	
		TAN_test();        //湿度检测
		num = Press_Number();
	
	}while(num!=4 && num!=3);
	
	if(num==4)
		page2();
	if(num==3)
		page3();
	
}

int page1()
{
	//显示主页
	//“智能晾衣架�
	//按3,A继续
	OLED_ShowCHinese(16,2,0);
	OLED_ShowCHinese(32,2,1);
	OLED_ShowCHinese(48,2,2);
	OLED_ShowCHinese(64,2,3);
	OLED_ShowCHinese(80,2,4);
	
  OLED_ShowCHinese(24,6,10);
	OLED_ShowNum(40,6,3,1,16);
	OLED_ShowString(48,6,",");
	OLED_ShowChar(56,6,'A');
	OLED_ShowCHinese(64,6,5);
	OLED_ShowCHinese(80,6,6);	
	
	return 0;
}

int page2()
{
	OLED_Clear();
	num=0;
	//显示第二页
	//温度
	//湿度
	//日期
	//按A返回	
	OLED_Clear();
	OLED_ShowCHinese(0,2,7);
	OLED_ShowCHinese(16,2,9);
	
	OLED_ShowCHinese(0,0,8);
	OLED_ShowCHinese(16,0,9);
	
//	OLED_ShowCHinese(0,4,15);
//	OLED_ShowCHinese(16,4,16);
		
		OLED_ShowCHinese(0,6,10);
	//OLED_ShowChar(16,6,'A');
	//OLED_ShowCHinese(32,6,5);
	//OLED_ShowCHinese(48,6,6);
		OLED_ShowString(16,6,"A");
		OLED_ShowCHinese(32,6,13);
		OLED_ShowCHinese(48,6,14);
	

		while(TAHSshow()!=1 && TAHSshow()!=2);
		
		if(TAHSshow()==2)
		{
			OLED_ShowCHinese(0,6,10);
		//OLED_ShowChar(16,6,'A');
		//OLED_ShowCHinese(32,6,5);
		//OLED_ShowCHinese(48,6,6);
			OLED_ShowString(16,6,"1");
			OLED_ShowCHinese(32,6,13);
			OLED_ShowCHinese(48,6,14);
			
			num=0;
			
			while(num!=1)
			num = Press_Number();	
			
			num=0;
			
			OLED_Clear();
			return 0;
		}
		
		do
		{
			num = Press_Number();	
			TAHSshow();
		}while(num!=1 && num!=2 && num!=4);
		

		if(num==1)  clo_move_front();
		else if(num==2)  clo_move_back();
		else if(num==4)	
		{
			num = 0;
			OLED_Clear();
			return 0;
		}
	num=0;


	OLED_Clear();
	return 0;
	
}

int page3()
{
	OLED_Clear();
	num=0;
	//显示第三页
	//按1出衣架
	//按2收衣架
	//按A返回
	OLED_ShowCHinese(0,0,10);
	OLED_ShowNum(16,0,2,1,16);
	OLED_ShowCHinese(32,0,17);
	OLED_ShowCHinese(48,0,3);
	OLED_ShowCHinese(64,0,4);
	
	OLED_ShowCHinese(0,2,10);
	OLED_ShowNum(16,2,1,1,16);
	OLED_ShowCHinese(32,2,18);
	OLED_ShowCHinese(48,2,3);
	OLED_ShowCHinese(64,2,4);
	
  OLED_ShowCHinese(24,6,10);
	OLED_ShowString(40,6,"A");
	OLED_ShowCHinese(56,6,13);
	OLED_ShowCHinese(72,6,14);
	

		do
		{
			num = Press_Number();	
		}while(num!=1 && num!=2 && num!=4);
		
		if(num==1)       clo_move_front();
		else if(num==2)  clo_move_back();
		else if(num==4)	 
		{
				num=0;
			OLED_Clear();
				return 0;
		}
		num=0;
	
	OLED_Clear();
	return 0;
}









