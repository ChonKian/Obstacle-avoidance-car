#include "srf05.h"


/*��¼��ʱ���������*/
unsigned int overcount=0;

/*****************************************
����˵����

PA2��Ϊ��ͨ���
PA3��Ϊ��ͨ����
*****************************************/

void Srf05_Init(void)
{
	//�ṹ��
	GPIO_InitTypeDef					GPIO_InitStruct;
	NVIC_InitTypeDef 					NVIC_InitStructer;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*TRIG�����ź�*/
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2;						//����2
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;			//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;		//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;				//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/*ECOH�����ź�*/
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_3;						//����3
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;					//����ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;				//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/*��ʱ��TIM3��ʼ��*/
	TIM_TimeBaseInitStruct.TIM_Prescaler			= 84-1;  								//84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period					= 1000-1;								//��ʱ����Ϊ1000
	TIM_TimeBaseInitStruct.TIM_CounterMode		= TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision	= TIM_CKD_DIV1;					//��Ƶ����
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);										//���������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructer.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructer);
	
	/*��ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM3, DISABLE);
}

u16 Get_Srf05_Value(void)
{
	u16 t = 0;
	u16 temp = 0, distance;
	
	//PA2Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	delay_us(10);
	//PA2Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	delay_us(20);
	//PA2Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	
	//���ö�ʱ����CNTΪ0  
	TIM3->CNT = 0;

	t = 0;
	//PA3�ȴ��ߵ�ƽ�������ο������ɿ����� while( ����ƽ  );
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
	{
		delay_us(1);
		
		t++;
		//5000*1 = 5000us = 5ms �ȴ�5msδ�иߵ�ƽ���򷵻�
		if(t >= 5000)
			return 0;
	}
	
	//ʹ�ܶ�ʱ����ʼ����
	TIM_Cmd(TIM3, ENABLE);
	
	t = 0;
	//PA3�ȴ��͵�ƽ�������ο������ɿ�����
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1)
	{
		delay_us(1);
		
		t++;
		//20000*1 = 20000us = 20ms �ȴ�20msδ�е͵�ƽ���򷵻�
		if(t >= 20000)
			return 0;
	}
	
	//��ȡ��ʱ��CNTֵ���Ӷ��õ��ߵ�ƽ����ʱ��    
	temp = TIM3->CNT;

	//�رն�ʱ��
	TIM_Cmd(TIM3, DISABLE);
	
	//ͨ����ʽ�������������������
	distance = temp/58;
	
	return distance;
}

float Senor_Using(void)
{
	u16 tim;
	unsigned int i=0;
	float length=0,sum=0;
	
	/*��5�����ݼ���һ��ƽ��ֵ*/
	while(i!=5)
	{
		//PA2Ϊ�ߵ�ƽ
		GPIO_SetBits(GPIOA, GPIO_Pin_2); //�����źţ���Ϊ�����ź�
		delay_us(20); //�ߵ�ƽ�źų���10us
		//PA2Ϊ�͵�ƽ
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		/*�ȴ������ź�*/
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET);
		TIM_Cmd(TIM3,ENABLE);//�����źŵ�����������ʱ������

		i+=1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==SET);//�����ź���ʧ
		TIM_Cmd(TIM3,DISABLE);//�رն�ʱ��

		tim=TIM_GetCounter(TIM3);//��ȡ��TIM4���Ĵ����еļ���ֵ��һ�߼�������ź�ʱ��

		length=(tim+overcount*1000)/58.0;//ͨ�������źż������

		sum=length+sum;
		TIM3->CNT=0; //��TIM4�����Ĵ����ļ���ֵ����
		overcount=0; //�ж������������
		delay_ms(10);
	}
	length=sum/5;
	return length;//������Ϊ��������ֵ
}

//�жϣ��������źźܳ��ǣ�����ֵ������ظ����������ж��������������
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־
		overcount++;
	}
}
