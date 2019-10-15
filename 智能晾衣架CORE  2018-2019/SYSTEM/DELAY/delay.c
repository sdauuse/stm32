#include "stm32w4k32s4.h"
#include "delay.h"
#include <intrins.h>

////////////////////ATTENTION///////////////////
//   
//   ������P37,P27   �ҵ��:P21,P45
//   ���ߵ�λ����������ѧ�麣ѧԺ
////////////////////////////////////////////////
void delay_1ms()
{
    unsigned char a,b;
    for(b=4;b>0;b--)
        for(a=113;a>0;a--);
}

void delay_1s(void)   //?? -0.000000000227us
{
    unsigned char a,b,c;
    for(c=13;c>0;c--)
        for(b=247;b>0;b--)
            for(a=142;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void delay_10ms()
{
    unsigned char a,b;
    for(b=249;b>0;b--)
        for(a=17;a>0;a--);
}



