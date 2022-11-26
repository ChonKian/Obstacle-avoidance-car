#include "usart1.h"


/*--------------------------------------------------*/
/*��������HC05 	Usart3_InitInit����					*/
/*��  ����PB10  ---- USART3_TX(���Ͷ�)				*/
/*		  PB11 	---- USART3_RX(���ն�)				*/
/*����ֵ��NOPE										*/
/*--------------------------------------------------*/

void Usart1_Init(int U1_BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
#if USART1_RX_ENABLE                         //���ʹ�ܽ��չ���
	NVIC_InitTypeDef NVIC_InitStructure;
#endif

	//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

	//ʹ��USART1ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//����ӳ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	//�ٶ�
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;    
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;	//����10
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//����11
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate 		= U1_BaudRate;			//������
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;	//�ֳ�
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;		//ֹͣλ
	USART_InitStructure.USART_Parity 		= USART_Parity_No;		//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
#if USART1_RX_ENABLE               												   //���ʹ�ܽ���ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //�շ�ģʽ
#else                                                                              //�����ʹ�ܽ���ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;	                           //ֻ��ģʽ
#endif
	USART_Init(USART1, &USART_InitStructure);

	//����NVIC���� �ڶ����� ��ռ���ȼ���Χ:0~3  ��Ӧ���ȼ���Χ��0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

#if USART1_RX_ENABLE  	         					        //���ʹ�ܽ���ģʽ

	USART_ClearFlag(USART1, USART_FLAG_RXNE);	            //������ձ�־λ
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          //���������ж�

	NVIC_InitStructure.NVIC_IRQChannel 						= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);							//����USARTx�ж�
#endif  

	/* ʹ�� USART */
	USART_Cmd(USART1, ENABLE);
}


/*-------------------------------------------------*/
/*������������3 printf����                         */
/*��  ����char* fmt,...  ��ʽ������ַ����Ͳ���    */
/*����ֵ����                                       */
/*-------------------------------------------------*/

__align(8) char Usart1_TxBuff[USART1_TXBUFF_SIZE];

void U1_Printf(char* fmt,...)
{
	unsigned int i,length;

	va_list ap;
	va_start(ap,fmt);
	vsprintf(Usart1_TxBuff,fmt,ap);
	va_end(ap);
	
	length=strlen((const char*)Usart1_TxBuff);
	while((USART1->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{
		USART1->DR = Usart1_TxBuff[i];
		while((USART1->SR&0X40)==0);
	}
}
