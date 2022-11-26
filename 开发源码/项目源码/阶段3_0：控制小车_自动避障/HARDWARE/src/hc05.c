#include "hc05.h"

/*-------------------------------------------------*/
/*��������HC05 	Usart3_InitInit����                */
/*��  ����PB10  ---- USART3_TX(���Ͷ�)			   */
/*		  PB11 	---- USART3_RX(���ն�)			   */
/*����ֵ����                                       */
/*-------------------------------------------------*/

void Hc05_Usart3_Init(int U3_BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE);

	//ʹ��USART1ʱ��
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//����ӳ��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	//�ٶ�
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;    
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10;				//����10
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//����11
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate 		= U3_BaudRate;															//������
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;											//�ֳ�
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;													//ֹͣλ
	USART_InitStructure.USART_Parity 		= USART_Parity_No;														//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//ȫ˫��
	USART_Init(USART3, &USART_InitStructure);

	//����NVIC���� ������� 0λΪ��ռ���ȼ�  4λΪ�����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* ����USARTx�ж� */
	NVIC_InitStructure.NVIC_IRQChannel 						= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//4���������ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* ʹ�� USART */
	USART_Cmd(USART3, ENABLE);
}


/*----------------------------------------------------*/
/*��������HC05		DATARecv����					  */
/*��  �������жϽ��յ����ݰ����������ǵ�INPUT�ṹ��	  */
/*����ֵ��INPUT���͵Ľṹ��                       	  */
/*----------------------------------------------------*/

INPUT DATARecv(void)
{
	uint8_t i;
	INPUT	_get_data;
	
	_Bool _mode;
	int  	_pwm_BA = 0;
	int  	_pwm_LR = 0;
	short _pwm_speed = 0;
	
	_mode = buffer[1];
	_get_data.mode = _mode;
	
	for(i=2;i<=3;i++){ 
		_pwm_speed += buffer[i]<<((i-2)*8);
	}
	_get_data.pwm_speed = _pwm_speed;
	
	for(i=4;i<=7;i++){ 
		_pwm_BA += buffer[i]<<((i-4)*8);
	}
	_get_data.pwm_BA = _pwm_BA;
	
	for(i=8;i<=11;i++){ 
		_pwm_LR += buffer[i]<<((i-8)*8);
	}
	_get_data.pwm_LR = _pwm_LR;
	
	_mode = 0;
	_pwm_BA = 0;
  _pwm_LR = 0;
	_pwm_speed = 0;
	
	return _get_data;
}


/*-------------------------------------------------*/
/*��������HC05		printf����                       */
/*��  ����char* fmt,...  ��ʽ������ַ����Ͳ���    */
/*����ֵ����                                       */
/*-------------------------------------------------*/

__align(8) char Usart3_TxBuff[USART3_TXBUFF_SIZE];

void Hc05_Printf(char* fmt,...)
{
	unsigned int i,length;

	va_list ap;
	va_start(ap,fmt);
	vsprintf(Usart3_TxBuff,fmt,ap);
	va_end(ap);
	
	length=strlen((const char*)Usart3_TxBuff);
	while((USART3->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{
		USART3->DR = Usart3_TxBuff[i];
		while((USART3->SR&0X40)==0);
	}
}
