#include "sys.h"
#include "TAHS.h"
#include "PWM.h"
////////////////////ATTENTION///////////////////
//   ������P37,P27   �ҵ��:P21,P45
//   ���ߵ�λ����������ѧ�麣ѧԺ
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
		if(a>=9)             //ʪ�ȴ���90
		{
			clo_move_back();   //�ջ�
		}
	}

}
