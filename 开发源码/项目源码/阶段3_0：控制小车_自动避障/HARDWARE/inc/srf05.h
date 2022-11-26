#ifndef __SRF05_H
#define __SRF05_H

#include "stm32f4xx.h"
#include "delay.h"


void	Srf05_Init(void);
u16 	Get_Srf05_Value(void);
float	Senor_Using(void);

#endif
