#ifndef __USART1_H
#define __USART1_H

#include "stm32f4xx.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"

#define USART1_RX_ENABLE     0      //是否开启接收功能  1：开启  0：关闭
#define USART1_TXBUFF_SIZE   256    //定义串口1 发送缓冲区大小 256字节

void Usart1_Init(int U1_BaudRate);
void U1_Printf(char* fmt,...);

#endif
