#include "stm32w4k32s4.h"
#include "sys.h"
#include "PWM.h"
#include "delay.h"
#include "oled.h"
#include "matrix buttons.h"
#include <math.h>

////////////////////ATTENTION///////////////////
//   ���������STM32W4K32S4-LQFP64S��Ƭ��
//   IO�����ã�
//   ������P01,P02   �ҵ��:P03,P04
//   enable1=P00;
//   enable2=P05;
//   ��ǰ��λ����  P10
//   �����λ����  P12
//	 ��ǰ��λ����  P11
//   �Һ���λ����  P13
//   ���ߵ�λ����������ѧ�麣ѧԺ
////////////////////////////////////////////////

#define PWMperiod 100  //PWM���ڣ�1000��0.1SΪһ������
#define Timer_InitValue_T4H  0x9c   //��ʱ����ֵ��9c9cΪ��ʱ100US
#define Timer_InitValue_T4L  0x9c
bit FLAG1=0;
u8 rotatetime=0;
/////////////////////////////////////////////////
sbit en1=P0^5; /* L298��Enable A */ 
sbit en2=P0^0; /* L298��Enable B */ 
sbit speed1=P0^4; /* L298��Input 1 */ 
sbit speed2=P0^3; /* L298��Input 2 */ 
sbit speed3=P0^1; /* L298��Input 3 */ 
sbit speed4=P0^2; /* L298��Input 4 */
//sbit INT1 = P3^3;

u8 m1=0;  /* ���1�ٶ�ֵ */ 
u8 m2=0; /* ���2�ٶ�ֵ */ 
u8 tmp1,tmp2; /* �����ǰ�ٶ�ֵ */ 
u8 speed;  //�趨��߳���
/////////////////////////////////////////////////


u8 Left_speedcontrol;
u8 Right_speedcontrol;
u16 motor_Leftspeed;
u16 motor_Rightspeed;
////////////////////////////////////////////////
//������:motorInit
//�������ã���ʼ���������
//������ע�����ռ��T4��ʱ��
////////////////////////////////////////////////
void motorInit()      
{
//	P3M0 |= (0<<7);       //����P37����ģʽΪ׼˫���
//	P3M1 |= (0<<7);
//	P2M0 |= (0<<7);       //����P27����ģʽΪ׼˫���
//	P2M1 |= (0<<7);

//	P2M0 |= (0<<1);       //����P21����ģʽΪ׼˫���
//	P2M1 |= (0<<1);
//	P4M0 |= (0<<5);       //����P45����ģʽΪ׼˫���
//	P4M1 |= (0<<5);
	
//	T4T3M &= 0x0f;       //��ʼ��T4T3M�Ĵ�����T4����
//	 T4H  = Timer_InitValue_T4H;    //װ�붨ʱ���ĳ�ֵ//�Զ��̶�Ϊ16λ�Զ���װģʽ
//   T4L  = Timer_InitValue_T4L;    //��ʱΪ100US     
//	 IE2  = 1<<6;        //��ʱ��4�����ж�																						    
//	T4T3M |= (1<<7); ;      //������ʱ��4
//	 EA   = 1;           //���ж�
	  TMOD=0x02; /* �趨T0�Ĺ���ģʽΪ2 */ 
	  TH0=0x9B; /* װ�붨ʱ���ĳ�ֵ */ 
	  TL0=0x9B; 
			
//		INT1 = 1;  //�����ⲿ�жϣ�INT1 P33��
//		IT1  = 0;
//		EX1  = 1;
		
	  EA=1; /* ���ж� */ 
	  ET0=1; /* ��ʱ��0�����ж� */ 																						    
	  TR0=1; /* ������ʱ��0 */ 
	  right_front_limit = 1;
  	left_front_limit  = 1;
  	right_beh_limit   = 1;
	  left_beh_limit    = 1;
		
}

////////////////////////////////////////////////
//������:motorPower
//�������ã������������
//������ע��	
////////////////////////////////////////////////
//void motorPower(u16 Leftspeed,u16 Rightspeed)
//{
//	#ifdef USE_OLED
//	//�������ռ�ձȲ����Ϲ涨������������
//	if(abs(*motor_Leftspeed)>PWMperiod && abs(*motor_Rightspeed)>PWMperiod)
//	{
//		OLED_ShowString(0,0,"motor speed error");
//		OLED_ShowString(0,2,"please enter new value");
//		OLED_ShowString(0,6,"FOR LEFT MOTOR:");
//		*motor_Leftspeed = martix_button_getchar8bit();
//		OLED_ShowString(0,0,"L:       R:      ");
//		OLED_ShowNum(15,0,*motor_Leftspeed,2,16);
//		*motor_Rightspeed = martix_button_getchar8bit();
//		OLED_ShowNum(50,0,*motor_Rightspeed,2,16);
//		OLED_ShowString(0,6,"OK,PLEASE ENTER #");
//		while(Press_Number()!='#');
//		clo_move();	  //����Ƕ�׵���
//	}
//	#endif
	////////////////////////////////////////////////
//	if(abs(Leftspeed)<PWMperiod && abs(Rightspeed)<PWMperiod)
//	{
//		Left_speedcontrol=abs(Leftspeed);
//		Right_speedcontrol=abs(Rightspeed);
//		if(motor_Leftspeed>0 && motor_Rightspeed>0)
//		{				 
//			MOTOR1_LEFT = 1;
//		  MOTOR1_RIGHT= 0;
//			MOTOR2_LEFT = 1;
//		  MOTOR2_RIGHT= 0;
//		}
//		else if(motor_Leftspeed<0 && motor_Rightspeed>0)
//		{
//			MOTOR1_LEFT = 0;
//		  MOTOR1_RIGHT= 1;
//			MOTOR2_LEFT = 1;
//		  MOTOR2_RIGHT= 0;
//		}
//		else if(motor_Leftspeed>0 && motor_Rightspeed<0)
//		{
//			MOTOR1_LEFT = 1;
//		  MOTOR1_RIGHT= 0;
//			MOTOR2_LEFT = 0;
//		  MOTOR2_RIGHT= 1;
//		}
//		else if(motor_Leftspeed<0 && motor_Rightspeed<0)
//		{
//			MOTOR1_LEFT = 0;
//		  MOTOR1_RIGHT= 1;
//			MOTOR2_LEFT = 0;
//		  MOTOR2_RIGHT= 1;
//		}
//	}
//}

////////////////////////////////////////////////
//������:TIMER4_Routine
//�������ã�PWM�жϷ�����
//������ע��	
////////////////////////////////////////////////
void TIMER0_Routine() interrupt TIMER0_VECTOR 
{
		if(rotatetime==0) /* 1��PWM������ɺ�Ż��������ֵ */ 
	{ 
		tmp1=m1; 
		tmp2=m2; 
	} 
	if(rotatetime<tmp1) en1=1; 
	else en1=0; /* �������1��PWM�ź� */ 
	if(rotatetime<tmp2) en2=1; 
	else en2=0; /* �������2��PWM�ź� */ 
	rotatetime++; 
	if(rotatetime>=100) 
	rotatetime=0; /* 1��PWM�ź���100���жϲ��� */ 
	
	if(Press_Number()==1)
		ET0=0;
	
	////////////////////////////////////////////////////////
//	if(rotatetimes<Left_speedcontrol)//�������1��PWM�ź�`1`
//	enable1=1;
//	else
//	enable1=0;
//	
//	if(rotatetimes<Right_speedcontrol)//�������2��PWM�ź�
//	enable2=1;
//	else
//	enable2=0;
//	
//	rotatetimes++;
//	
//	if(rotatetimes>=PWMperiod)//һ�������Ժ�ѭ��������־��0
//	rotatetimes = 0;
}

////////////////////////////////////////////////
//������:clo_move_front
//��������: ʹ�¼��ƶ�����
//�������룺u8 dis,u16 left,u16 right
//��������:dis ��������ƶ��ľ���  left �����ٶ� right �ҵ���ٶ�
////////////////////////////////////////////////
void clo_move_front()
{
	ET0=1;
	OLED_Clear();
	OLED_ShowString(0,2,"PLEASE WAIT");
	OLED_ShowString(0,4,"PRESS 1 TO STOP");
	en1=en2=1;
	do
	{
		motorPower(33,95);
	}while(right_front_limit!=0	&& left_front_limit!=0);
	
	while(right_front_limit!=0)
	{
		en1=0;	
		motorPower(0,95);
	}
	
	while(left_front_limit!=0)
	{
		en2=0;
		motorPower(33,0);
	}
	en1=en2=0;
	
	speed1=speed2=speed3=speed4=0;
	
	OLED_Clear();
	OLED_ShowString(0,4,"SUCCESS");
	delay_1s();
	OLED_Clear();
	FLAG1=1;
	EX0=EX1=1;
	ET0=0;
}

////////////////////////////////////////////////
//������:clo_move_back
//�������ã�ʹ�¼��ƶ�����
//�������룺u8 dis,u16 left,u16 right
//��������:dis ��������ƶ��ľ���  left �����ٶ� right �ҵ���ٶ�
////////////////////////////////////////////////
void clo_move_back()
{
//	if(right_beh_limit!=0 && left_beh_limit!=0)
//	while(1)
//	{
//		if(right_beh_limit!=0)
//		{
//			motorPower(-93,0);
//		}
//		if(left_beh_limit!=0)
//		{
//			motorPower(0,90);
//		}
//		if(right_beh_limit!=0 && left_beh_limit!=0)
//			break;
//	}
	ET0=1;
	OLED_Clear();
	OLED_ShowString(0,4,"PLEASE WAIT");
	en1=en2=1;
	do
	{
		motorPower(-30,-95);
	}while(right_beh_limit!=0 && left_beh_limit!=0);
	
	while(right_beh_limit!=0)
	{
		en1=0;
		motorPower(0,-95);
	}
	
	while(left_beh_limit!=0)
	{
		en2=0;
		motorPower(-30,0);
	}
	en1=en2=0;
	
	speed1=speed2=speed3=speed4=0;
	
	OLED_Clear();
	OLED_ShowString(0,4,"SUCCESS");
	delay_1s();
	OLED_Clear();
	rain1=rain2=1;
	FLAG1=0;
	ET0=0;
}
////////////////////////////////////////////////
//������:motorPower
//�������ã������������
//������ע��	
////////////////////////////////////////////////
void motorPower(char leftspeed, char rightspeed) 
{

	if(rightspeed>=-100 && rightspeed<=100) 
	{ 
		m2=abs(rightspeed); /* ���1���ٶȿ��� */ 
		if(rightspeed<0) /* ���1�ķ������ */ 
		{ 
			speed3=0; 
			speed4=1; 
		} 
		else 
		{ 
			speed3=1; 
			speed4=0; 
		} 
	} 
	if(leftspeed>=-100 && leftspeed<=100) 
	{ 
		m1=abs(leftspeed); /* ȡ�ٶȵľ���ֵ */ 
		if(leftspeed<0) /* �ٶ�ֵΪ����ת */ 
		{ 
			speed1=0; 
			speed2=1; 
		} 
		else /* ��Ϊ��������ת */ 
		{ 
			speed1=1; 
			speed2=0; 
		} 
	} 
} 














