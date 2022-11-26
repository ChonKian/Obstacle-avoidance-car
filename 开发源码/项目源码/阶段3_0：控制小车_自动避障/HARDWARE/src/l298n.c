#include "l298n.h"


/*****************************************
����˵����

������֡���������PD14��PD15;

TIM4_CH3(TIM4 -- APB1 16λ  84MHZ)
TIM4_CH4(TIM4 -- APB1 16λ  84MHZ)

*****************************************/

void L298n_Ctrl1_Init(void)
{
	//�ṹ��
	GPIO_InitTypeDef  				GPIO_InitStruct;
	TIM_OCInitTypeDef					TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseInitStruct;
	
	//ʹ��TIM4ʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	//ʹ��GPIODʱ�ӣ�
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode		= GPIO_Mode_AF;					//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;				//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz; 		//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;					//����
	
	//��ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_14;						//����14
	GPIO_Init(GPIOD, &GPIO_InitStruct);	
	
	//��ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_15;						//����15
	GPIO_Init(GPIOD, &GPIO_InitStruct);	

	//GPIOD14/15����ӳ�䵽��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); 
	
	//��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1);									//84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);									//ARR   ��1000,��1MHZ��PWM����1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;					//��Ƶ����
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//��ʼ������Ƚϲ��� OC3 -- ͨ��3	OC4 -- ͨ��4
	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;								//PWMģʽ1
	TIM_OCInitStruct.TIM_OCPolarity	= TIM_OCPolarity_High;					//������Ե�ƽ ������ѡ��ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse 		= 0;															//CCR1 = 0;
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;				//ͨ��ʹ��
	TIM_OC3Init(TIM4, &TIM_OCInitStruct);
	TIM_OC4Init(TIM4, &TIM_OCInitStruct);
	
	//ʹ��Ԥװ�ؼĴ���  OC3 -- ͨ��3	OC4 -- ͨ��4
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	//ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	//ʹ�ܶ�ʱ����
	TIM_Cmd(TIM4, ENABLE);
}


/*****************************************
����˵����

������֡���������PE13��PE14;

TIM1_CH3(TIM1 -- APB2 16λ  168MHZ)
TIM1_CH4(TIM1 -- APB2 16λ  168MHZ)

*****************************************/

void L298n_Ctrl2_Init(void)
{
	//�ṹ��
	GPIO_InitTypeDef					GPIO_InitStruct;
	TIM_OCInitTypeDef					TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseInitStruct;
	
	//ʹ��TIM1ʱ�ӣ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	//ʹ��GPIOEʱ�ӣ�
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode		= GPIO_Mode_AF;					//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;				//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;			//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;					//����
	
	//��ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_13;						//����13
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	
	//��ʼ��IO��Ϊ���ù��������
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_14;						//����14
	GPIO_Init(GPIOE, &GPIO_InitStruct);	

	//GPIOE13/14����ӳ�䵽��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); 
	
	//��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInitStruct.TIM_Prescaler			= (168-1); 										//168��Ƶ 168MHZ/168 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period					= (1000-1);										//ARR   ��1000,��1MHZ��PWM����1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode		= TIM_CounterMode_Up;					//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision	= TIM_CKD_DIV1;								//��Ƶ����
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	
	//��ʼ������Ƚϲ��� OC3 -- ͨ��3	OC4 -- ͨ��4
	TIM_OCInitStruct.TIM_OCMode								= TIM_OCMode_PWM2;									//PWMģʽ2
	TIM_OCInitStruct.TIM_OCPolarity						= TIM_OCPolarity_Low;								//������Ե�ƽ ������ѡ��͵�ƽ
	TIM_OCInitStruct.TIM_Pulse								= 0;																//CCR1 = 0;
	TIM_OCInitStruct.TIM_OutputState					= TIM_OutputState_Enable;						//ͨ��ʹ��
	TIM_OCInitStruct.TIM_OCIdleState					= TIM_OCIdleState_Reset;						//����״̬���͵�ƽ
	
	TIM_OC3Init(TIM1, &TIM_OCInitStruct);
	TIM_OC4Init(TIM1, &TIM_OCInitStruct);
	
	//ʹ��Ԥװ�ؼĴ���  OC3 -- ͨ��3	OC4 -- ͨ��4
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	//ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	//MOE �����ʹ��,�߼���ʱ�����뿪�����
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	//ʹ�ܶ�ʱ����
	TIM_Cmd(TIM1, ENABLE);
}


void Car_Go(void)
{
	//����
	TIM_SetCompare4(TIM1, 0);
	TIM_SetCompare3(TIM1, 300);
	//����
	TIM_SetCompare4(TIM4, 0);
	TIM_SetCompare3(TIM4, 300);
}

void Car_Stop(void)
{
	//����
	TIM_SetCompare3(TIM1, 0);
	TIM_SetCompare4(TIM1, 0);
	//����
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 0);
}

void Car_Back(void)
{
	//����
	TIM_SetCompare3(TIM1, 0);
	TIM_SetCompare4(TIM1, 300);
	//����
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 300);
}

void Car_Left(void)
{
	//����
	TIM_SetCompare3(TIM1, 0);
	TIM_SetCompare4(TIM1, 300);
	//����
	TIM_SetCompare4(TIM4, 0);
	TIM_SetCompare3(TIM4, 300);
}

void Car_BigLeft(void)
{
	//����
	TIM_SetCompare3(TIM1, 0);
	TIM_SetCompare4(TIM1, 400);
	//����
	TIM_SetCompare4(TIM4, 0);
	TIM_SetCompare3(TIM4, 400);
}

void Car_Right(void)
{
	//����
	TIM_SetCompare4(TIM1, 0);
	TIM_SetCompare3(TIM1, 300);
	//����
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 300);
	
}

void Car_BigRight(void)
{
	//����
	TIM_SetCompare4(TIM1, 0);
	TIM_SetCompare3(TIM1, 400);
	//����
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 400);
	
}
