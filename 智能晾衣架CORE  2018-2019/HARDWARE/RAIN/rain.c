#include "stm32w4k32s4.h"
#include "sys.h"
#include "rain.h"

void RainInit()
{
	P3=0xff;
	EA=1;  //�����ж�
	EX0=EX1=0; //���ⲿ�ж�
	IT0=IT1=1; //�����ش��� 
}


//void exint0() interrupt 0
//{
//			clo_move_back();	//�����ⲿ�жϼ����δ�������״̬
//			EX0=EX1=0;
//}
//void exint1() interrupt 2
//{
//			clo_move_back();
//			EX0=EX1=0;
//}
