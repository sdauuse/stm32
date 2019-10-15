#include "stm32w4k32s4.h"
#include "delay.h"
#include "matrix buttons.h"
#include "sys.h"

////////////////////ATTENTION///////////////////
//   ���������STM32W4K32S4-LQFP64S��Ƭ��
//   ������̵�����ΪP60-P67
//   ���ߵ�λ����������ѧ�麣ѧԺ
////////////////////////////////////////////////
#define GPIO_KEY P6


////////////////////////////////////////////////////////	
//������:Press_Number
//�������ã�ʶ��4X4���󰴼������µļ����������ض�Ӧֵ
//������ע��	
////////////////////////////////////////////////////////
u8 Press_Number()
{
	u8 KeyValue;
  char a=0;
	char g=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay_10ms();//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{
			
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //��ⰴ�����ּ��
			{
				delay_10ms();
				g++;
			}
		}
	}

	return KeyValue;
}

////////////////////////////////////////////////////////	
//������:martix_button_getchar4bit
//�������ã����þ�����̵õ�һ����λ16�����������ض�Ӧ��ֵ
//������ע��	
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











