#include "car_ctrl.h"

uint8_t Forward_or_Backward = 0;
uint8_t Leftward_or_Rightward = 0;

PWM_SPEED Get_PWM(void)
{
	PWM_SPEED _speed;
	
	//�ж����ݽ�����ɱ�־λ
	if (GetData_Done == 1) {
		bluetooth_data = DATARecv();

		//��ȡ ǰ��/���˵�ռ�ձ�(�ٶ�)
		if (bluetooth_data.pwm_BA <= 0)
		{
			if (bluetooth_data.pwm_BA == 0.0) {
				
				_speed.Forward = 0;
				_speed.Backward = 0;
				Forward_or_Backward = 0;
				
			} else {
				
				_speed.Forward = 0;
				_speed.Backward = __fabs(bluetooth_data.pwm_BA);
				Forward_or_Backward = 2;
			}
		
		} else {
		
			_speed.Backward = 0;
			_speed.Forward = bluetooth_data.pwm_BA;
			Forward_or_Backward = 1;
		}
		
		//��ȡ ��/�ҵ�ռ�ձ�(�ٶ�)
		if (bluetooth_data.pwm_LR <= 0)
		{
			if (bluetooth_data.pwm_LR == 0.0) {
				
				_speed.Leftward = 0;
				_speed.Rightward = 0;
				Leftward_or_Rightward = 0;
				
			} else if (bluetooth_data.pwm_LR < -150) {
				
				_speed.Leftward = 0;
				_speed.Rightward = __fabs(bluetooth_data.pwm_LR);
				Leftward_or_Rightward = 2;
				
			} else {
				
				_speed.Leftward = 0;
				_speed.Rightward = 0;
				Leftward_or_Rightward = 0;
			}
			
		} else if (bluetooth_data.pwm_LR > 150) {
			
			_speed.Rightward = 0;
			_speed.Leftward = bluetooth_data.pwm_LR;
			Leftward_or_Rightward = 1;
			
		} else {
			
			_speed.Leftward = 0;
			_speed.Rightward = 0;
			Leftward_or_Rightward = 0;
		}
		
		if (bluetooth_data.pwm_speed < _speed.Forward)
			_speed.Forward = bluetooth_data.pwm_speed;
		if (bluetooth_data.pwm_speed < _speed.Backward)
			_speed.Backward = bluetooth_data.pwm_speed;
		if (bluetooth_data.pwm_speed < _speed.Leftward)
			_speed.Leftward = bluetooth_data.pwm_speed;
		if (bluetooth_data.pwm_speed < _speed.Rightward)
			_speed.Rightward = bluetooth_data.pwm_speed;
	}
	return _speed;
}


void Car_Ctrl(void)
{
	PWM_SPEED speed;
	speed = Get_PWM();
	
	if(Forward_or_Backward == 0 && Leftward_or_Rightward == 0) {						//�жϱ�־λ -- ֹͣ
		
		TIM_SetCompare3(TIM1, 0);
		TIM_SetCompare4(TIM1, 0);
		TIM_SetCompare3(TIM4, 0);
		TIM_SetCompare4(TIM4, 0);
		
	} else if(Forward_or_Backward == 1) {							//�жϱ�־λ -- ǰ��
		
		if (Leftward_or_Rightward == 0) {								//�жϱ�־λ -- ֱ��

			//����
			TIM_SetCompare3(TIM4, speed.Forward);
			TIM_SetCompare4(TIM4, 0);
			//����
			TIM_SetCompare3(TIM1, speed.Forward);
			TIM_SetCompare4(TIM1, 0);
			
		} else if (Leftward_or_Rightward == 1) {				//�жϱ�־λ -- ǰ����ת
			
			//����
			TIM_SetCompare3(TIM1, speed.Forward);
			TIM_SetCompare4(TIM1, 0);
			//����
			TIM_SetCompare3(TIM4, speed.Leftward);
			TIM_SetCompare4(TIM4, 0);
			
		} else if (Leftward_or_Rightward == 2) {				//�жϱ�־λ -- ǰ����ת
			
			//����
			TIM_SetCompare3(TIM1, speed.Rightward);
			TIM_SetCompare4(TIM1, 0);
			//����
			TIM_SetCompare3(TIM4, speed.Forward);
			TIM_SetCompare4(TIM4, 0);
		}

	} else if(Forward_or_Backward == 2) {						//�жϱ�־λ -- ����
		
		if (Leftward_or_Rightward == 0) {							//�жϱ�־λ -- ֱ
			
			//����
			TIM_SetCompare3(TIM4, 0);
			TIM_SetCompare4(TIM4, speed.Backward);
			//����
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, speed.Backward);
			
		}else if (Leftward_or_Rightward == 1) {				//�жϱ�־λ -- ������ת
			
			//����
			TIM_SetCompare3(TIM4, 0);
			TIM_SetCompare4(TIM4, speed.Leftward);
			//����
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, speed.Backward);
			
		}else if (Leftward_or_Rightward == 2) {				//�жϱ�־λ -- ������ת
			
			//����
			TIM_SetCompare3(TIM4, 0);
			TIM_SetCompare4(TIM4, speed.Backward);
			//����
			TIM_SetCompare3(TIM1, 0);
			TIM_SetCompare4(TIM1, speed.Rightward);
		}
	}
}
