#ifndef SYS_H
#define SYS_H
#include "stm32w4k32s4.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned int 
	
#define TIMER0_VECTOR 1 //��ʱ��0�жϺ�
#define TIMER1_VECTOR 3  //��ʱ��1�жϺ�
#define TIMER2_VECTOR 12 //��ʱ��2�жϺ�
#define TIMER3_VECTOR 19 //��ʱ��3�жϺ�
#define TIMER4_VECTOR 20 //��ʱ��4�жϺ�

sbit rain1=P1^5;
sbit rain2=P1^6;
void TAN_test();
#endif 
