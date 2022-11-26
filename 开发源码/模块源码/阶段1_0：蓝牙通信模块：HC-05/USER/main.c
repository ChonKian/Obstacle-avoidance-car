#include "stm32f4xx.h"
#include "delay.h"
#include "hc05.h"

extern u8 GetData_Done;
extern char buffer[32];

int main(void)
{
	Delay_Init();
	Hc05_Usart3_Init(9600);

	while(1)
	{
		if (GetData_Done == 1) {
			Hc05_Printf("%d\r\n",buffer);
		}
	}
}
