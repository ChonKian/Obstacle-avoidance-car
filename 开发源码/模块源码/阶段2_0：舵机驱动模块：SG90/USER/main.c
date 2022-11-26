#include "stm32f4xx.h"
#include "delay.h"
#include "sg90.h"

int main(void)
{
	Delay_Init();
	
	Sg90_Init();
	
	while (1)
	{
		SG90_Right_90;
		delay_s(1);
		SG90_Right_45;
		delay_s(1);
		SG90_Front;
		delay_s(1);
		SG90_Left_45;
		delay_s(1);
		SG90_Left_90;
		delay_s(1);
	}
}
