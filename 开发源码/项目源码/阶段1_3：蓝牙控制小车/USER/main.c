#include "stm32f4xx.h"
#include "car_ctrl.h"
#include "delay.h"
#include "l298n.h"
#include "hc05.h"

int main(void)
{
	Delay_Init();
	L298n_Ctrl1_Init();
	L298n_Ctrl2_Init();
	Hc05_Usart3_Init(9600);

	while(1)
	{
		Car_Ctrl();
	}
}
