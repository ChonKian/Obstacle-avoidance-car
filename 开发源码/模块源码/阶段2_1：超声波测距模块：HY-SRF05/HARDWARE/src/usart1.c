#include "usart1.h"


/*--------------------------------------------------*/
/*函数名：HC05 	Usart3_InitInit函数					*/
/*参  数：PB10  ---- USART3_TX(发送端)				*/
/*		  PB11 	---- USART3_RX(接收端)				*/
/*返回值：NOPE										*/
/*--------------------------------------------------*/

void Usart1_Init(int U1_BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
#if USART1_RX_ENABLE                         //如果使能接收功能
	NVIC_InitTypeDef NVIC_InitStructure;
#endif

	//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);

	//使能USART1时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//引脚映射
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	//速度
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;    
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;	//引脚10
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//引脚11
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate 		= U1_BaudRate;			//波特率
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;	//字长
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;		//停止位
	USART_InitStructure.USART_Parity 		= USART_Parity_No;		//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件控制流
#if USART1_RX_ENABLE               												   //如果使能接收模式
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //收发模式
#else                                                                              //如果不使能接收模式
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;	                           //只发模式
#endif
	USART_Init(USART1, &USART_InitStructure);

	//设置NVIC分组 第二分组 抢占优先级范围:0~3  响应优先级范围：0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

#if USART1_RX_ENABLE  	         					        //如果使能接收模式

	USART_ClearFlag(USART1, USART_FLAG_RXNE);	            //清除接收标志位
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          //开启接收中断

	NVIC_InitStructure.NVIC_IRQChannel 						= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);							//启用USARTx中断
#endif  

	/* 使能 USART */
	USART_Cmd(USART1, ENABLE);
}


/*-------------------------------------------------*/
/*函数名：串口3 printf函数                         */
/*参  数：char* fmt,...  格式化输出字符串和参数    */
/*返回值：无                                       */
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
