# Obstacle-avoidance-car
 基于STM32F407的超声波避障小车

## 接线说明

### 主控芯片<br>
-------------------------------
 * MCU：<br>
	 * STM32F407ZET6

### 蓝牙串口通信模块<br>
-------------------------------
 * HC_05：<br>
	 * STATE&nbsp;&nbsp;&nbsp;-------&emsp;X&emsp;&emsp;&emsp;状态指示端：空脚<br>
	 * RXD&emsp;&ensp;-------&emsp;PB10&emsp;&nbsp;蓝牙输入端：引脚复用：USART3_TX<br>
	 * TXD&emsp;&ensp;-------&emsp;PB11&emsp;&nbsp;蓝牙输出端：引脚复用：USART3_RX<br>
	 * GND&emsp;&thinsp;-------&emsp;GND&emsp;&nbsp;蓝牙接地端：板载接地<br>
	 * VCC&emsp;&ensp;-------&emsp;VCC&emsp;&nbsp;&nbsp;蓝牙供电端：板载供电 +5V<br>
	 * EN&emsp;&emsp;-------&emsp;X&emsp;&emsp;&ensp;&nbsp;蓝牙使能端：空脚<br>

### 电机驱动板模块<br>
-------------------------------
 * L298N：<br>
	 * IN1	-------	PE13	电机_左轮：	引脚复用：PWM	TIM1_CH3<br>
	 * IN2	-------	PE14	电机_左轮：	引脚复用：PWM	TIM1_CH4<br>
	 * IN3	-------	PD14	电机_右轮：	引脚复用：PWM	TIM4_CH3<br>
	 * IN4	-------	PD15    电机_右轮：	引脚复用：PWM	TIM4_CH4<br>

### 舵机驱动模块<br>
-------------------------------
 * SG90：<br>
	 * VCC&emsp;&emsp;&nbsp;------- VCC&ensp;&nbsp;舵机供电端：        板载供电 +5V<br>
	 * PWM_IN	------- PE5&ensp;&ensp;舵机脉冲输入端：    引脚复用：PWM   TIM9_CH1<br>
	 * GND&emsp;&emsp;------- GND&ensp;舵机供电端：        板载接地<br>

### 超声波测距模块<br>
-------------------------------
 * HY-SRF05：<br>
	 * VCC&emsp;------- VCC 超声波供电端：              板载供电 +5V<br>
	 * TRIG&emsp;------- PA2 超声波触发控制端：          普通输出：GPIOA_Pin_2<br>
	 * ECHO &thinsp;------- PA3 超声波回响信号端：          普通输出：GPIOA_Pin_3<br>
	 * OUT&emsp;&thinsp;------- X   超声波开关量输出端：        空脚<br>
	 * GND&emsp;------- GND 超声波供电端：              板载接地<br>

## 数据协议

### 蓝牙串口通讯<br>
-------------------------------
 * HC_05数据包协议：<br>
	 * 包头&emsp;&ensp;-&ensp;1字节&emsp;-&ensp;固定值：0x5A<br>
	 * 数据&emsp;&ensp;-&ensp;自定义 &thinsp;-&ensp;自定义<br>
	 * 效验和 &thinsp;-&ensp;1字节&emsp;-&ensp;数据所有字节之和的低8位<br>
	 * 包尾&emsp;&ensp;-&ensp;1字节&emsp;-&ensp;固定值：0x5A<br>
