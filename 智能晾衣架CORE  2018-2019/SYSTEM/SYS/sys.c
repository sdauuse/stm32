#include "sys.h"
#include "TAHS.h"
#include "PWM.h"
////////////////////ATTENTION///////////////////
//   左电机：P37,P27   右电机:P21,P45
//   作者单位：北京理工大学珠海学院
////////////////////////////////////////////////
 
void TAN_test()
{
	unsigned char a;
	if(FLAG1==1)
	{
		if(rain1==0&&rain2==0)
		{
			clo_move_back();
		}
		RH();
		a=U8RH_data_H/10;
		if(a>=9)             //湿度大于90
		{
			clo_move_back();   //收回
		}
	}

}
