//#include "get_distance.h"
#include "stm32f4xx.h"
#include "car_ctrl.h"
#include "car_auto.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "l298n.h"
#include "srf05.h"
#include "hc05.h"
#include "sg90.h"

INPUT	bluetooth_data;

int main(void)
{
	Sg90_Init();
	Srf05_Init();
	Delay_Init();
	L298n_Ctrl1_Init();
	L298n_Ctrl2_Init();
	Hc05_Usart3_Init(9600);

	while(1)
	{
		if (GetData_Done == 1) {
			
			bluetooth_data = DATARecv();
		
			if (bluetooth_data.mode == 1) {
				Car_Auto();
			} else {
				Car_Ctrl();
			}
		}
	}
}
