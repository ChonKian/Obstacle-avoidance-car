#ifndef __L298N_H
#define __L298N_H

#include "stm32f4xx.h"


void L298n_Ctrl1_Init(void);
void L298n_Ctrl2_Init(void);

void Car_Go(void);
void Car_Stop(void);
void Car_Back(void);
void Car_Left(void);
void Car_BigLeft(void);
void Car_Right(void);
void Car_BigRight(void);

#endif
