#include "stm32w4k32s4.h"
#include "sys.h"
#include "PWM.h"
#include "delay.h"
#include "oled.h"
#include "matrix buttons.h"
#include <math.h>

////////////////////ATTENTION///////////////////
//   本程序基于STM32W4K32S4-LQFP64S单片机
//   IO口设置：
//   左电机：P01,P02   右电机:P03,P04
//   enable1=P00;
//   enable2=P05;
//   左前限位开关  P10
//   左后限位开关  P12
//	 右前限位开关  P11
//   右后限位开关  P13
//   作者单位：北京理工大学珠海学院
////////////////////////////////////////////////

#define PWMperiod 100  //PWM周期，1000即0.1S为一个周期
#define Timer_InitValue_T4H  0x9c   //计时器初值，9c9c为定时100US
#define Timer_InitValue_T4L  0x9c
bit FLAG1=0;
u8 rotatetime=0;
/////////////////////////////////////////////////
sbit en1=P0^5; /* L298的Enable A */ 
sbit en2=P0^0; /* L298的Enable B */ 
sbit speed1=P0^4; /* L298的Input 1 */ 
sbit speed2=P0^3; /* L298的Input 2 */ 
sbit speed3=P0^1; /* L298的Input 3 */ 
sbit speed4=P0^2; /* L298的Input 4 */
//sbit INT1 = P3^3;

u8 m1=0;  /* 电机1速度值 */ 
u8 m2=0; /* 电机2速度值 */ 
u8 tmp1,tmp2; /* 电机当前速度值 */ 
u8 speed;  //设定最高车速
/////////////////////////////////////////////////


u8 Left_speedcontrol;
u8 Right_speedcontrol;
u16 motor_Leftspeed;
u16 motor_Rightspeed;
////////////////////////////////////////////////
//函数名:motorInit
//函数作用：初始化电机驱动
//函数备注：电机占用T4定时器
////////////////////////////////////////////////
void motorInit()      
{
//	P3M0 |= (0<<7);       //设置P37工作模式为准双向口
//	P3M1 |= (0<<7);
//	P2M0 |= (0<<7);       //设置P27工作模式为准双向口
//	P2M1 |= (0<<7);

//	P2M0 |= (0<<1);       //设置P21工作模式为准双向口
//	P2M1 |= (0<<1);
//	P4M0 |= (0<<5);       //设置P45工作模式为准双向口
//	P4M1 |= (0<<5);
	
//	T4T3M &= 0x0f;       //初始化T4T3M寄存器的T4部分
//	 T4H  = Timer_InitValue_T4H;    //装入定时器的初值//自动固定为16位自动重装模式
//   T4L  = Timer_InitValue_T4L;    //定时为100US     
//	 IE2  = 1<<6;        //定时器4允许中断																						    
//	T4T3M |= (1<<7); ;      //启动定时器4
//	 EA   = 1;           //开中断
	  TMOD=0x02; /* 设定T0的工作模式为2 */ 
	  TH0=0x9B; /* 装入定时器的初值 */ 
	  TL0=0x9B; 
			
//		INT1 = 1;  //开启外部中断（INT1 P33）
//		IT1  = 0;
//		EX1  = 1;
		
	  EA=1; /* 开中断 */ 
	  ET0=1; /* 定时器0允许中断 */ 																						    
	  TR0=1; /* 启动定时器0 */ 
	  right_front_limit = 1;
  	left_front_limit  = 1;
  	right_beh_limit   = 1;
	  left_beh_limit    = 1;
		
}

////////////////////////////////////////////////
//函数名:motorPower
//函数作用：电机驱动函数
//函数备注：	
////////////////////////////////////////////////
//void motorPower(u16 Leftspeed,u16 Rightspeed)
//{
//	#ifdef USE_OLED
//	//如果输入占空比不符合规定，则重新输入
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
//		clo_move();	  //函数嵌套调用
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
//函数名:TIMER4_Routine
//函数作用：PWM中断服务函数
//函数备注：	
////////////////////////////////////////////////
void TIMER0_Routine() interrupt TIMER0_VECTOR 
{
		if(rotatetime==0) /* 1个PWM周期完成后才会接受新数值 */ 
	{ 
		tmp1=m1; 
		tmp2=m2; 
	} 
	if(rotatetime<tmp1) en1=1; 
	else en1=0; /* 产生电机1的PWM信号 */ 
	if(rotatetime<tmp2) en2=1; 
	else en2=0; /* 产生电机2的PWM信号 */ 
	rotatetime++; 
	if(rotatetime>=100) 
	rotatetime=0; /* 1个PWM信号由100次中断产生 */ 
	
	if(Press_Number()==1)
		ET0=0;
	
	////////////////////////////////////////////////////////
//	if(rotatetimes<Left_speedcontrol)//产生电机1的PWM信号`1`
//	enable1=1;
//	else
//	enable1=0;
//	
//	if(rotatetimes<Right_speedcontrol)//产生电机2的PWM信号
//	enable2=1;
//	else
//	enable2=0;
//	
//	rotatetimes++;
//	
//	if(rotatetimes>=PWMperiod)//一个周期以后循环次数标志回0
//	rotatetimes = 0;
}

////////////////////////////////////////////////
//函数名:clo_move_front
//函数作用: 使衣架移动程序
//函数输入：u8 dis,u16 left,u16 right
//参数作用:dis 定义参数移动的距离  left 左电机速度 right 右电机速度
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
//函数名:clo_move_back
//函数作用：使衣架移动程序
//函数输入：u8 dis,u16 left,u16 right
//参数作用:dis 定义参数移动的距离  left 左电机速度 right 右电机速度
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
//函数名:motorPower
//函数作用：电机驱动函数
//函数备注：	
////////////////////////////////////////////////
void motorPower(char leftspeed, char rightspeed) 
{

	if(rightspeed>=-100 && rightspeed<=100) 
	{ 
		m2=abs(rightspeed); /* 电机1的速度控制 */ 
		if(rightspeed<0) /* 电机1的方向控制 */ 
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
		m1=abs(leftspeed); /* 取速度的绝对值 */ 
		if(leftspeed<0) /* 速度值为负则反转 */ 
		{ 
			speed1=0; 
			speed2=1; 
		} 
		else /* 不为负数则正转 */ 
		{ 
			speed1=1; 
			speed2=0; 
		} 
	} 
} 














