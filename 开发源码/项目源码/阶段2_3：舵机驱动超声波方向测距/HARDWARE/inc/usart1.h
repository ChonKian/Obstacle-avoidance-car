#ifndef __USART1_H
#define __USART1_H

#include "stm32f4xx.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"

#define USART1_RX_ENABLE     0      //�Ƿ������չ���  1������  0���ر�
#define USART1_TXBUFF_SIZE   256    //���崮��1 ���ͻ�������С 256�ֽ�

void Usart1_Init(int U1_BaudRate);
void U1_Printf(char* fmt,...);

#endif
