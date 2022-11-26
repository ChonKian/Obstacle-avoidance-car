#include "sg90.h"


/*****************************************
引脚说明：

LED0连接在PF9,低电平灯亮；高电平，灯灭
TIM14_CH1(TIM14 -- APB1 16位  84MHZ)

*****************************************/


void Sg90_Init(void)
{
	GPIO_InitTypeDef					GPIO_InitStruct;
	TIM_OCInitTypeDef					TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	
	//（2）使能定时器14和相关IO口时钟。
	//使能定时器14时钟：
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	//使能GPIOF时钟：
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_5;		//引脚9	
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF;		//复用模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;	//输出推挽
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz; //速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	//（3）初始化IO口为复用功能输出。
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	//（4）GPIOF9复用映射到定时器14
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); 
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (16800-1); 	//168分频 168MHZ/168 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (200-1);	//ARR   计200,在1MHZ，PWM周期1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM2;	//PWM模式1
	TIM_OCInitStruct.TIM_OCPolarity	= TIM_OCPolarity_High;//输出极性电平 ，这里选择低电平
	TIM_OCInitStruct.TIM_Pulse 		= 0; //CCR1 = 0;
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable; //通道使能
	//（6）初始化输出比较参数 OC1 -- 通道1	
	TIM_OC1Init(TIM9, &TIM_OCInitStruct);
	
	//（7）使能预装载寄存器  OC1 -- 通道1	
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); 
	//（8）使能自动重装载的预装载寄存器允许位	
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	//（9）使能定时器。
	TIM_Cmd(TIM9, ENABLE);
}
