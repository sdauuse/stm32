#ifndef SYS_H
#define SYS_H
#include "stm32w4k32s4.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned int 
	
#define TIMER0_VECTOR 1 //定时器0中断号
#define TIMER1_VECTOR 3  //定时器1中断号
#define TIMER2_VECTOR 12 //定时器2中断号
#define TIMER3_VECTOR 19 //定时器3中断号
#define TIMER4_VECTOR 20 //定时器4中断号

sbit rain1=P1^5;
sbit rain2=P1^6;
void TAN_test();
#endif 
