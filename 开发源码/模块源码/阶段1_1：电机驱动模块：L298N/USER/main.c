#include "stm32f4xx.h"
#include "delay.h"
#include "l298n.h"

int main(void)
{
	Delay_Init();
	
	L298n_Ctrl1_Init();
	L298n_Ctrl2_Init();
	
	Car_Go();
	
	while (1);
}
