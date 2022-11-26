#ifndef __HC05_H
#define __HC05_H

#include "stm32f4xx.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"

#define REC_BUF_SIZE 			14    		//�������ݰ��Ĵ�С
#define USART3_TXBUFF_SIZE		256			//���崮��1 ���ͻ�������С 256�ֽ�

extern char buffer[32];

typedef struct {
	_Bool mode;
	short pwm_speed;
	int  	pwm_BA;
	int  	pwm_LR;
}INPUT;

INPUT DATARecv(void);
void Hc05_Printf(char* fmt,...);
void Hc05_Usart3_Init(int myBaudRate);

#endif
