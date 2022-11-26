#ifndef __CAR_CTRL_H
#define __CAR_CTRL_H

#include "stm32f4xx.h"
#include "delay.h"
#include "math.h"
#include "hc05.h"

extern u8 GetData_Done;
extern INPUT bluetooth_data;

extern u16 distance_right;
extern u16 distance_forward_right;
extern u16 distance_forward;
extern u16 distance_forward_left;
extern u16 distance_left;

typedef struct {
	int Forward;
	int Backward;
	int Leftward;
	int Rightward;
}PWM_SPEED;

PWM_SPEED Get_PWM(void);
void Car_Ctrl(void);

#endif
