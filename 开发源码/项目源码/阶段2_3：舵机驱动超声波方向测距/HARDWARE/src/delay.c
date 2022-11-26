#include "delay.h"

u32 my_us = 21;  	//在21MHZ 1us 计21个数。
u32 my_ms = 21000;  //在21MHZ 1ms 计21000个数。

void Delay_Init(void)
{
	//选择Systick定时器时钟 HCLK/8 = 168MHZ/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

//u32 == unsigned int 
//nus最大值：798915
void delay_us(u32 nus)
{
	u32 temp = 0x00;
	
	//设置重装载值寄存器
	SysTick->LOAD = nus*my_us - 1;
	//设置当前值寄存器值为0
	SysTick->VAL = 0x00;
	
	//启动定时器
	SysTick->CTRL |= (0x01<<0);
	
	do{
		temp = SysTick->CTRL;
		//判断是否开启定时器	判断第16是否为1,若为1，退出查询
	}while(  (temp & (0x01<<0)) && ( !(temp & (0x01<<16))));
	
	
	//关闭定时器
	SysTick->CTRL &= ~(0x01<<0);	
	

}


//u32 == unsigned int 
//nus最大值：798
void delay_ms(u32 nms)
{
	u32 temp = 0x00;
	
	//设置重装载值寄存器
	SysTick->LOAD = nms*my_ms - 1;
	//设置当前值寄存器值为0
	SysTick->VAL = 0x00;
	
	//启动定时器
	SysTick->CTRL |= (0x01<<0);
	
	do{
		temp = SysTick->CTRL;
		//判断是否开启定时器	判断第16是否为1,若为1，退出查询
	}while(  (temp & (0x01<<0)) && ( !(temp & (0x01<<16))));
	
	
	//关闭定时器
	SysTick->CTRL &= ~(0x01<<0);	
	
}

void delay_s(u32 ns)
{
	int i;
	
	for(i=0; i<ns; i++)
	{
		delay_ms(500);
		delay_ms(500);
	}
}

