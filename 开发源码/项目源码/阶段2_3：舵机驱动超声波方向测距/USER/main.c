#include "stm32f4xx.h"
#include "usart1.h"
#include "delay.h"
#include "srf05.h"
#include "sg90.h"

int main(void)
{
	Delay_Init();
	
	Sg90_Init();
	Srf05_Init();
	Usart1_Init(9600);
	
	while(1)
	{
		SG90_Right_90;
		delay_ms(500);
		float right_90_distance =  Senor_Using();
		delay_s(1);
		U1_Printf("Right 90бу Distance:%.2f\r\n",right_90_distance);
		
		SG90_Right_45;
		delay_ms(500);
		float right_45_distance =  Senor_Using();
		delay_s(1);
		U1_Printf("Right 45бу Distance:%.2f\r\n",right_45_distance);
		
		SG90_Front;
		delay_ms(500);
		float front_distance =  Senor_Using();
		delay_s(1);
		U1_Printf("Front Distance:%.2f\r\n",front_distance);
		
		SG90_Left_45;
		delay_ms(500);
		float left_45_distance =  Senor_Using();
		delay_s(1);
		U1_Printf("Left 45бу Distance:%.2f\r\n",left_45_distance);
		
		SG90_Left_90;
		delay_ms(500);
		float left_90_distance =  Senor_Using();
		delay_s(1);
		U1_Printf("Left 90бу Distance:%.2f\r\n",left_90_distance);
	}
}
