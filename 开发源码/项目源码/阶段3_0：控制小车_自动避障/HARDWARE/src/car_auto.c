#include "car_auto.h"

void Car_Auto(void)
{
	u16 _distance_forward;
	u16 _distance_forward_left;
	u16 _distance_forward_right;
	
	SG90_Front;
	delay_ms(100);
	_distance_forward = Senor_Using();
	delay_ms(100);
	
	if(_distance_forward > 50) Car_Go();
	
	if(_distance_forward < 50) {
		Car_Stop();
		
		//���
		SG90_Left_45;
		delay_ms(700);
		_distance_forward_left = Senor_Using();
		
		SG90_Right_45;
		delay_ms(700);
		_distance_forward_right = Senor_Using();
		
		SG90_Front;
		delay_ms(100);
		if(_distance_forward_left > _distance_forward_right) {
			do {
				SG90_Front;						 //�������
				delay_ms(10);
				_distance_forward = Senor_Using();	//�ظ���ǰ���ľ���ͬʱ��ת
				delay_ms(10);						
				Car_Left();
			}
			while(_distance_forward < 50);		//һֱת��ǰ���������30cm		
		}
		if(_distance_forward_left < _distance_forward_right) {
			do {
			SG90_Front;
			delay_ms(10);
				_distance_forward = Senor_Using();  //�ظ���ǰ���ľ���ͬʱ��ת
			delay_ms(10);						
			Car_Right();
			}
			while(_distance_forward < 50);		//һֱת��ǰ���������30cm
		}
	}
}
