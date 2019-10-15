////////////////////ATTENTION///////////////////
//   ���������STM32W4K32S4-LQFP64S��Ƭ��
//   ������̵�����ΪP60-P67
//   ���ߵ�λ����������ѧ�麣ѧԺ
//
//����  �ռ���ʪ������ ���� 11.0592M
//////////////////////////////////////////////////
#ifndef __TAHS_H__
#define __TAHS_H__
#include "stc15w4k32s4.h"
#include "intrins.h"
#include "oled.h"
#include "sys.h"

#define uchar unsigned char
#define uint unsigned int
#define   Data_0_time    4

//----------------IO�ڶ�����--------------------//



//----------------������--------------------//
extern u8  U8FLAG,k;
extern u8  U8count,U8temp;
extern u8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
extern u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
extern u8  U8comdata;
extern u8  outdata[5];  //���巢�͵��ֽ���	   
extern u8  indata[5];
extern u8  count, count_r;
extern u8  str[5];
extern u16 U16temp1,U16temp2;


void COM(void);
void Delay_30us(void);
void delay_20ms();
void SendData(u8 *a);
void TAHSInit();

//-----ʪ�ȶ�ȡ�ӳ��� ------------
int RH(void);
u8 TAHSshow();//��ʾ��ʪ�Ⱥ���
		
		
#endif
		
		
		
		
