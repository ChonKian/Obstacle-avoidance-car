#include "hc05.h"

/*-------------------------------------------------*/
/*函数名：HC05 	Usart3_InitInit函数                */
/*参  数：PB10  ---- USART3_TX(发送端)			   */
/*		  PB11 	---- USART3_RX(接收端)			   */
/*返回值：无                                       */
/*-------------------------------------------------*/

void Hc05_Usart3_Init(int U3_BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE);

	//使能USART1时钟
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//引脚映射
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;	//速度
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;    
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10;				//引脚10
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//引脚11
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate 		= U3_BaudRate;															//波特率
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;											//字长
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;													//停止位
	USART_InitStructure.USART_Parity 		= USART_Parity_No;														//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//全双工
	USART_Init(USART3, &USART_InitStructure);

	//设置NVIC分组 第零分组 0位为抢占优先级  4位为次优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* 启用USARTx中断 */
	NVIC_InitStructure.NVIC_IRQChannel 						= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//4、检测接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* 使能 USART */
	USART_Cmd(USART3, ENABLE);
}


/*----------------------------------------------------*/
/*函数名：HC05		DATARecv函数					  */
/*参  数：将中断接收的数据包导出到我们的INPUT结构体	  */
/*返回值：INPUT类型的结构体                       	  */
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
/*函数名：HC05		printf函数                       */
/*参  数：char* fmt,...  格式化输出字符串和参数    */
/*返回值：无                                       */
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
