//****************************************************************//
//	   DHT21ʹ�÷��� 
//��Ƭ�� AT89S52 �� STC89C52RC 
//����   ���ڷ�����ʪ������ ���� 11.0592M ������ 9600 
//Ӳ��   P2.0��ΪͨѶ������DHT11,DHT11�ĵ�Դ�͵����ӵ�Ƭ���ĵ�Դ�͵أ���Ƭ�����ڼ�MAX232���ӵ��� 
//****************************************************************//
////////////////////ATTENTION///////////////////
//   ���������STM32W4K32S4-LQFP64S��Ƭ��
//   ������̵�����ΪP60-P67
//   ���ߵ�λ����������ѧ�麣ѧԺ
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
u8  outdata[5];  //���巢�͵��ֽ���	   
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
	   	//��ʱ������forѭ��		  
	   	if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		  // ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 
		   U8comdata<<=1;
	   	 U8comdata|=U8temp;        //0
	     }//rof
	   
	   
	}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== U8T_data_H------
	//----�¶ȵ�8λ== U8T_data_L------
	//----ʪ�ȸ�8λ== U8RH_data_H-----
	//----ʪ�ȵ�8λ== U8RH_data_L-----
	//----У�� 8λ == U8checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

	int RH(void)
	{
	  //��������18ms 
     flag=0;
		delay_20ms();
	   flag=1;

	  //������������������ ������ʱ20us
		Delay_30us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 

	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	 
			flag=1;
		 if(!flag)		 //T !	  
	   {
			 U8FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
			 while((!flag)&&U8FLAG++);
			 U8FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
			 while((flag)&&U8FLAG++);
		 //���ݽ���״̬		 
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
		 //����У�� 
			
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
//������:TAHSInit
//�������ã���ʼ����ʪ�ȴ�����
//������ע��	
////////////////////////////////////////////////////////	
void TAHSInit()
{
	OLED_Clear();
  CLK_DIV =0x40;

}

////////////////////////////////////////////////////////	
//������:TAHSshow
//��������:��ʾ��ʪ�Ⱥ���
//������ע��	
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
		OLED_ShowNum(64,0,U8RH_data_H,2,16);//��ʾʪ������
	  OLED_ShowString(80,0,".");
		OLED_ShowNum(96,0,U8RH_data_L,2,16);//��ʾʪ��С��

		OLED_ShowCHinese(0,2,7);
		OLED_ShowCHinese(16,2,9);
		OLED_ShowNum(64,2,U8T_data_H,2,16);	//��ʾ�¶�����
		OLED_ShowString(80,2,".");
		OLED_ShowNum(96,2,U8T_data_L,2,16);	//��ʾ�¶�С��

		//OLED_ShowString(32,4,"2017");
		
		OLED_ShowString(0,4,"successed");
	
		return 1;
}
////////////////////ʹ�÷���//////////////////////////////////////////////	
//----------------------------------------------
//main()��������:  AT89C51  11.0592MHz 	���ڷ� 
//����ʪ������,������ 9600 
//----------------------------------------------
//void main()
//{
//	U8  i,j;
//	
//	//uchar str[6]={"RS232"};
//	/* ϵͳ��ʼ�� */
//	OLED_Init();
//
//	TMOD = 0x20;	  //��ʱ��T1ʹ�ù�����ʽ2
//	TH1 = 253;        // ���ó�ֵ
//	TL1 = 253;
//	TR1 = 1;          // ��ʼ��ʱ
//	SCON = 0x50;	  //������ʽ1��������9600bps���������   
//	ES = 1;
//	EA = 1;           // �������ж�   
//	TI = 0;
//	RI = 0;
//	SendData(str);   //���͵����� 
//	Delay(1);         //��ʱ100US��12M����)
//	OLED_Clear();
//	while(1)
//	{  
//
//	   //------------------------
//	   //������ʪ�ȶ�ȡ�ӳ��� 
//	    RH();
//
//	
//		
//		OLED_ShowString(24,0,"SUREN");
//
//		OLED_ShowCHinese(0,2,2);   //ʪ
//		OLED_ShowCHinese(16,2,1);  //��
//		OLED_ShowNum(32,2,U8RH_data_H,3,16);//��ʾʪ������
////	    OLED_ShowString(40,2,".");
////		OLED_ShowNum(,2,U8RH_data_L,3,16);//��ʾʪ��С��
//
//		OLED_ShowCHinese(0,4,0);   //��
//		OLED_ShowCHinese(16,4,1);  //��
//		OLED_ShowNum(32,4,U8T_data_H,3,16);	//��ʾ�¶�����
////		OLED_ShowString(40,4,".");
////		OLED_ShowNum(48,4,U8T_data_L,3,16);	//��ʾ�¶�С��
//
//		OLED_ShowCHinese(0,6,3);   //��
//		OLED_ShowCHinese(16,6,4);  //��
//		OLED_ShowString(40,6,"2016/7/20");
//
//		Delay(50000);
//	}
//}
