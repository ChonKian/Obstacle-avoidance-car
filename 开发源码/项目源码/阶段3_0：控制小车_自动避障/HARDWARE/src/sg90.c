#include "sg90.h"


/*****************************************
����˵����

LED0������PF9,�͵�ƽ�������ߵ�ƽ������
TIM14_CH1(TIM14 -- APB1 16λ  84MHZ)

*****************************************/


void Sg90_Init(void)
{
	GPIO_InitTypeDef					GPIO_InitStruct;
	TIM_OCInitTypeDef					TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	
	//��2��ʹ�ܶ�ʱ��14�����IO��ʱ�ӡ�
	//ʹ�ܶ�ʱ��14ʱ�ӣ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	//ʹ��GPIOFʱ�ӣ�
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_5;		//����9	
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;	//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz; //�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	//��3����ʼ��IO��Ϊ���ù��������
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	//��4��GPIOF9����ӳ�䵽��ʱ��14
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); 
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (16800-1); 	//168��Ƶ 168MHZ/168 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (200-1);	//ARR   ��200,��1MHZ��PWM����1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM2;	//PWMģʽ1
	TIM_OCInitStruct.TIM_OCPolarity	= TIM_OCPolarity_High;//������Ե�ƽ ������ѡ��͵�ƽ
	TIM_OCInitStruct.TIM_Pulse 		= 0; //CCR1 = 0;
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable; //ͨ��ʹ��
	//��6����ʼ������Ƚϲ��� OC1 -- ͨ��1	
	TIM_OC1Init(TIM9, &TIM_OCInitStruct);
	
	//��7��ʹ��Ԥװ�ؼĴ���  OC1 -- ͨ��1	
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); 
	//��8��ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ	
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	//��9��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM9, ENABLE);
}
