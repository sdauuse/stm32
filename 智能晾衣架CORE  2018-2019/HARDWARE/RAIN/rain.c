#include "stm32w4k32s4.h"
#include "sys.h"
#include "rain.h"

void RainInit()
{
	P3=0xff;
	EA=1;  //开总中断
	EX0=EX1=0; //开外部中断
	IT0=IT1=1; //跳变沿触发 
}


//void exint0() interrupt 0
//{
//			clo_move_back();	//利用外部中断检测雨滴传感器的状态
//			EX0=EX1=0;
//}
//void exint1() interrupt 2
//{
//			clo_move_back();
//			EX0=EX1=0;
//}
