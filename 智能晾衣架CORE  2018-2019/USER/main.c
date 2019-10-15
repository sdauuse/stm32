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
 	TAHSInit();   //��ʪ�ȴ�������ʼ��    
	OLED_Init();  //oled��ʼ��
	motorInit();  //�����ʼ��
	RainInit();   //��δ�������ʼ��
	P6=0x00;
	
	
	
	while(1)
	{	
		page1();   
		RUN();          //��������
	}
}














