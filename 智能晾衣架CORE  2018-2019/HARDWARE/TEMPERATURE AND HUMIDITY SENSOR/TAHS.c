//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//****************************************************************//
////////////////////ATTENTION///////////////////
//   本程序基于STM32W4K32S4-LQFP64S单片机
//   矩阵键盘的引脚为P60-P67
//   作者单位：北京理工大学珠海学院
////////////////////////////////////////////////

#include "stc15w4k32s4.h"
#include "intrins.h"
#include "oled.h"
#include "sys.h"
#include "TAHS.h"
#include "delay.h"

sbit flag=P4^0;

u8  U8FLAG,k;
u8  U8count,U8temp;
u8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
u8  U8comdata;
u8  outdata[5];  //定义发送的字节数	   
u8  indata[5];
u8  count, count_r;
u8  str[5];
u16 U16temp1,U16temp2;

//void Delay(u16 j)
//{      u8 i;
//	    for(;j>0;j--)
//	  { 	
//		for(i=0;i<27;i++);

//	  }
//}
// 
void delay_20ms(void)   //?? -0.868055555558us
{
    unsigned char a,b,c;
    for(c=133;c>0;c--)
        for(b=20;b>0;b--)
            for(a=40;a>0;a--);
}


void  Delay_30us(void)
{
   unsigned char a;
    for(a=163;a>0;a--);
}

void  COM(void)
{
     u8 i;
          
      for(i=0;i<8;i++)	   
	    {
		
	    U8FLAG=2;	
	   	while((!P02)&&U8FLAG++);
			Delay_30us();
	  	U8temp=0;
	    if(flag)U8temp=1;
		  U8FLAG=2;
		  while((flag)&&U8FLAG++);
	   	//超时则跳出for循环		  
	   	if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
	   	   
		  // 如果高电平高过预定0高电平值则数据位为 1 
	   	 
		   U8comdata<<=1;
	   	 U8comdata|=U8temp;        //0
	     }//rof
	   
	   
	}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== U8T_data_H------
	//----温度低8位== U8T_data_L------
	//----湿度高8位== U8RH_data_H-----
	//----湿度低8位== U8RH_data_L-----
	//----校验 8位 == U8checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

	int RH(void)
	{
	  //主机拉低18ms 
     flag=0;
		delay_20ms();
	   flag=1;

	  //总线由上拉电阻拉高 主机延时20us
		Delay_30us();
	 //主机设为输入 判断从机响应信号 

	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	 
			flag=1;
		 if(!flag)		 //T !	  
	   {
			 U8FLAG=2;
		 //判断从机是否发出 80us 的低电平响应信号是否结束	 
			 while((!flag)&&U8FLAG++);
			 U8FLAG=2;
		 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
			 while((flag)&&U8FLAG++);
		 //数据接收状态		 
			 COM();
			 U8RH_data_H_temp=U8comdata;
			 COM();
			 U8RH_data_L_temp=U8comdata;
			 COM();
			 U8T_data_H_temp=U8comdata;
			 COM();
			 U8T_data_L_temp=U8comdata;
			 COM();
			 U8checkdata_temp=U8comdata;
			 flag=1;
		 //数据校验 
			
			 U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
			 if(U8temp==U8checkdata_temp)
			 {
					U8RH_data_H=U8RH_data_H_temp;
					U8RH_data_L=U8RH_data_L_temp;
					U8T_data_H=U8T_data_H_temp;
					U8T_data_L=U8T_data_L_temp;
					U8checkdata=U8checkdata_temp;
			 }//fi
	   }//fi
		if(U8RH_data_H!=0&&U8T_data_H!=0)
		 return 1;
		else return 0;
	}
////////////////////////////////////////////////////////	
//函数名:TAHSInit
//函数作用：初始化温湿度传感器
//函数备注：	
////////////////////////////////////////////////////////	
void TAHSInit()
{
	OLED_Clear();
  CLK_DIV =0x40;

}

////////////////////////////////////////////////////////	
//函数名:TAHSshow
//函数作用:显示温湿度函数
//函数备注：	
////////////////////////////////////////////////////////
u8 TAHSshow()
{
		u8 time=0;
	  RH();
		while(RH()!=1 && time <=100)
		{
			time++;
			OLED_ShowString(0,4,"Being received..");
		}
		if(time>100)
		{
			OLED_Clear();
			OLED_ShowString(0,2,"received failed");
			delay_1s();
			delay_1s();
			delay_1s();
			delay_1s();
						
			OLED_Clear();
			
			OLED_ShowString(0,2,"try again..");
			delay_1s();
			delay_1s();
			delay_1s();
			delay_1s();
			
			OLED_Clear();
					
			return 2;
		}
		time=0;
		OLED_Clear();

		OLED_ShowCHinese(0,0,8);
		OLED_ShowCHinese(16,0,9);
		OLED_ShowNum(64,0,U8RH_data_H,2,16);//显示湿度整数
	  OLED_ShowString(80,0,".");
		OLED_ShowNum(96,0,U8RH_data_L,2,16);//显示湿度小数

		OLED_ShowCHinese(0,2,7);
		OLED_ShowCHinese(16,2,9);
		OLED_ShowNum(64,2,U8T_data_H,2,16);	//显示温度整数
		OLED_ShowString(80,2,".");
		OLED_ShowNum(96,2,U8T_data_L,2,16);	//显示温度小数

		//OLED_ShowString(32,4,"2017");
		
		OLED_ShowString(0,4,"successed");
	
		return 1;
}
////////////////////使用范例//////////////////////////////////////////////	
//----------------------------------------------
//main()功能描述:  AT89C51  11.0592MHz 	串口发 
//送温湿度数据,波特率 9600 
//----------------------------------------------
//void main()
//{
//	U8  i,j;
//	
//	//uchar str[6]={"RS232"};
//	/* 系统初始化 */
//	OLED_Init();
//
//	TMOD = 0x20;	  //定时器T1使用工作方式2
//	TH1 = 253;        // 设置初值
//	TL1 = 253;
//	TR1 = 1;          // 开始计时
//	SCON = 0x50;	  //工作方式1，波特率9600bps，允许接收   
//	ES = 1;
//	EA = 1;           // 打开所以中断   
//	TI = 0;
//	RI = 0;
//	SendData(str);   //发送到串口 
//	Delay(1);         //延时100US（12M晶振)
//	OLED_Clear();
//	while(1)
//	{  
//
//	   //------------------------
//	   //调用温湿度读取子程序 
//	    RH();
//
//	
//		
//		OLED_ShowString(24,0,"SUREN");
//
//		OLED_ShowCHinese(0,2,2);   //湿
//		OLED_ShowCHinese(16,2,1);  //度
//		OLED_ShowNum(32,2,U8RH_data_H,3,16);//显示湿度整数
////	    OLED_ShowString(40,2,".");
////		OLED_ShowNum(,2,U8RH_data_L,3,16);//显示湿度小数
//
//		OLED_ShowCHinese(0,4,0);   //温
//		OLED_ShowCHinese(16,4,1);  //度
//		OLED_ShowNum(32,4,U8T_data_H,3,16);	//显示温度整数
////		OLED_ShowString(40,4,".");
////		OLED_ShowNum(48,4,U8T_data_L,3,16);	//显示温度小数
//
//		OLED_ShowCHinese(0,6,3);   //日
//		OLED_ShowCHinese(16,6,4);  //期
//		OLED_ShowString(40,6,"2016/7/20");
//
//		Delay(50000);
//	}
//}
