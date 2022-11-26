#include "srf05.h"


/*记录定时器溢出次数*/
unsigned int overcount=0;

/*****************************************
引脚说明：

PA2做为普通输出
PA3做为普通输入
*****************************************/

void Srf05_Init(void)
{
	//结构体
	GPIO_InitTypeDef					GPIO_InitStruct;
	NVIC_InitTypeDef 					NVIC_InitStructer;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	
	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能定时器3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*TRIG触发信号*/
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2;						//引脚2
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//输出模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;			//输出推挽
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;		//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;				//上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/*ECOH回响信号*/
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_3;						//引脚3
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;					//输入模式
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;				//上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/*定时器TIM3初始化*/
	TIM_TimeBaseInitStruct.TIM_Prescaler			= 84-1;  								//84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period					= 1000-1;								//定时周期为1000
	TIM_TimeBaseInitStruct.TIM_CounterMode		= TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision	= TIM_CKD_DIV1;					//分频因子
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);										//开启更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructer.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructer);
	
	/*不使能定时器*/
	TIM_Cmd(TIM3, DISABLE);
}

u16 Get_Srf05_Value(void)
{
	u16 t = 0;
	u16 temp = 0, distance;
	
	//PA2为低电平
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	delay_us(10);
	//PA2为高电平
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	delay_us(20);
	//PA2为低电平
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	
	//设置定时器的CNT为0  
	TIM3->CNT = 0;

	t = 0;
	//PA3等待高电平到来，参考按键松开代码 while( 读电平  );
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
	{
		delay_us(1);
		
		t++;
		//5000*1 = 5000us = 5ms 等待5ms未有高电平，则返回
		if(t >= 5000)
			return 0;
	}
	
	//使能定时器开始计数
	TIM_Cmd(TIM3, ENABLE);
	
	t = 0;
	//PA3等待低电平到来，参考按键松开代码
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1)
	{
		delay_us(1);
		
		t++;
		//20000*1 = 20000us = 20ms 等待20ms未有低电平，则返回
		if(t >= 20000)
			return 0;
	}
	
	//获取定时器CNT值，从而得到高电平持续时间    
	temp = TIM3->CNT;

	//关闭定时器
	TIM_Cmd(TIM3, DISABLE);
	
	//通过公式计算出超声波测量距离
	distance = temp/58;
	
	return distance;
}

float Senor_Using(void)
{
	u16 tim;
	unsigned int i=0;
	float length=0,sum=0;
	
	/*测5次数据计算一次平均值*/
	while(i!=5)
	{
		//PA2为高电平
		GPIO_SetBits(GPIOA, GPIO_Pin_2); //拉高信号，作为触发信号
		delay_us(20); //高电平信号超过10us
		//PA2为低电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		/*等待回响信号*/
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET);
		TIM_Cmd(TIM3,ENABLE);//回响信号到来，开启定时器计数

		i+=1; //每收到一次回响信号+1，收到5次就计算均值
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==SET);//回响信号消失
		TIM_Cmd(TIM3,DISABLE);//关闭定时器

		tim=TIM_GetCounter(TIM3);//获取计TIM4数寄存器中的计数值，一边计算回响信号时间

		length=(tim+overcount*1000)/58.0;//通过回响信号计算距离

		sum=length+sum;
		TIM3->CNT=0; //将TIM4计数寄存器的计数值清零
		overcount=0; //中断溢出次数清零
		delay_ms(10);
	}
	length=sum/5;
	return length;//距离作为函数返回值
}

//中断，当回响信号很长是，计数值溢出后重复计数，用中断来保存溢出次数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志
		overcount++;
	}
}
