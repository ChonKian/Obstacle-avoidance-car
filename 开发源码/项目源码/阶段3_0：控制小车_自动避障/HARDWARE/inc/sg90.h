#ifndef __SG90_H
#define __SG90_H

#include "stm32f4xx.h"

#define   SG90_Right_90     TIM_SetCompare1(TIM9, 175)
#define   SG90_Right_45			TIM_SetCompare1(TIM9, 180)
#define   SG90_Front				TIM_SetCompare1(TIM9, 185)
#define   SG90_Left_45			TIM_SetCompare1(TIM9, 190)
#define   SG90_Left_90			TIM_SetCompare1(TIM9, 195)


void Sg90_Init(void);



#endif
