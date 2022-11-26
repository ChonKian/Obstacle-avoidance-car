#include "delay.h"

u32 my_us = 21;  	//��21MHZ 1us ��21������
u32 my_ms = 21000;  //��21MHZ 1ms ��21000������

void Delay_Init(void)
{
	//ѡ��Systick��ʱ��ʱ�� HCLK/8 = 168MHZ/8 = 21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

//u32 == unsigned int 
//nus���ֵ��798915
void delay_us(u32 nus)
{
	u32 temp = 0x00;
	
	//������װ��ֵ�Ĵ���
	SysTick->LOAD = nus*my_us - 1;
	//���õ�ǰֵ�Ĵ���ֵΪ0
	SysTick->VAL = 0x00;
	
	//������ʱ��
	SysTick->CTRL |= (0x01<<0);
	
	do{
		temp = SysTick->CTRL;
		//�ж��Ƿ�����ʱ��	�жϵ�16�Ƿ�Ϊ1,��Ϊ1���˳���ѯ
	}while(  (temp & (0x01<<0)) && ( !(temp & (0x01<<16))));
	
	
	//�رն�ʱ��
	SysTick->CTRL &= ~(0x01<<0);	
	

}


//u32 == unsigned int 
//nus���ֵ��798
void delay_ms(u32 nms)
{
	u32 temp = 0x00;
	
	//������װ��ֵ�Ĵ���
	SysTick->LOAD = nms*my_ms - 1;
	//���õ�ǰֵ�Ĵ���ֵΪ0
	SysTick->VAL = 0x00;
	
	//������ʱ��
	SysTick->CTRL |= (0x01<<0);
	
	do{
		temp = SysTick->CTRL;
		//�ж��Ƿ�����ʱ��	�жϵ�16�Ƿ�Ϊ1,��Ϊ1���˳���ѯ
	}while(  (temp & (0x01<<0)) && ( !(temp & (0x01<<16))));
	
	
	//�رն�ʱ��
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

