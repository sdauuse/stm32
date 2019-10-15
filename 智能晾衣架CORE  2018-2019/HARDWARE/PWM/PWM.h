#ifndef __PWM_H_
#define __PWM_H_
#include "stm32w4k32s4.h"
#include "sys.h"
#include "delay.h"

sbit MOTOR1_LEFT  = P0^1;
sbit MOTOR1_RIGHT = P0^2;
sbit MOTOR2_LEFT  = P0^3;
sbit MOTOR2_RIGHT = P0^4;

sbit enable1=P0^0;
sbit enable2=P0^5;

sbit right_front_limit = P1^1;
sbit left_front_limit  = P1^7;
sbit right_beh_limit   = P1^3;
sbit left_beh_limit    = P1^2;


extern u8 rotatetimes;
extern u8 Left_speedcontrol;
extern u8 Right_speedcontrol;
extern u16 motor_Leftspeed;
extern u16 motor_Rightspeed;
extern bit FLAG1;
void TIMER0_Routine();
void motorInit();
//void motorPower(u16 Leftspeed,u16 Rightspeed);
void clo_move_front();
void clo_move_back();
void motorPower(char speed2, char speed1);
void TIMER0_Routine();













#endif

