#include "stm32f4xx.h"
#include "usart1.h"
#include "delay.h"
#include "srf05.h"

int main(void)
{
	Delay_Init();
	
	Srf05_Init();
	Usart1_Init(9600);
	
	while(1)
	{
		delay_ms(500);
		
		float distance =  Senor_Using();
		U1_Printf("Distance:%.2f\r\n",distance);
	}
}
