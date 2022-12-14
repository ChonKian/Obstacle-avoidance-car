/**
  @page TIM_DMA TIM DMA example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    TIM/TIM_DMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Description of the TIM DMA example.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This example shows how to use DMA with TIM1 Update request to transfer Data from
memory to TIM1 Capture Compare Register 3 (CCR3).

The following configuration values are used in this example:
 - TIM1CLK = SystemCoreClock 
 - Prescaler = 0 
 - TIM1 counter clock = SystemCoreClock
 - SystemCoreClock is set to 168 MHz for STM32F4xx

The objective is to configure TIM1 channel 3 to generate complementary PWM 
(Pulse With Modulation) signal with a frequency equal to 17.57 KHz, and a variable 
duty cycle that is changed by the DMA after a specific number of Update DMA request.

The number of this repetitive requests is defined by the TIM1 Repetition counter,
each 3 Update Requests, the TIM1 Channel 3 Duty Cycle changes to the next new 
value defined by the aSRC_Buffer.


@par Directory contents 
  
  - TIM/TIM_DMA/system_stm32f4xx.c   STM32F4xx system clock configuration file
  - TIM/TIM_DMA/stm32f4xx_conf.h     Library Configuration file
  - TIM/TIM_DMA/stm32f4xx_it.c       Interrupt handlers
  - TIM/TIM_DMA/stm32f4xx_it.h       Interrupt handlers header file
  - TIM/TIM_DMA/main.c               Main program
  - TIM/TIM_DMA/main.h               Main program header file

      
@par Hardware and Software environment 

  - This example runs on STM32F405xx/407xx, STM32F415xx/417xx, STM32F427xx/437xx and 
    STM32F429xx/439xx devices.
    
  - This example has been tested with STMicroelectronics STM324xG-EVAL (STM32F40xx/
    STM32F41xx Devices), STM32437I-EVAL (STM32F427xx/STM32F437xx Devices) and 
    STM324x9I-EVAL RevB (STM32F429xx/STM32F439xx Devices) evaluation boards and 
    can be easily tailored to any other supported device and development board.

  - STM324xG-EVAL/STM32437I-EVAL and STM324x9I-EVAL RevB Set-up 
    - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms: 
        - TIM1 CH3  (PA.10)
        - TIM1 CH3N (PB.15) 
         

@par How to use it ? 

In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\STM32F4xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Select the project workspace related to the used device 
   - If "STM32F40_41xxx" is selected as default project Add the following files in the project source list:
     - Utilities\STM32_EVAL\STM3240_41_G_EVAL\stm324xg_eval.c
           
   - If "STM32F427_437xx" is selected as default project Add the following files in the project source list:
     - Utilities\STM32_EVAL\STM324x7I_EVAL\stm324x7i_eval.c
          
   - If "STM32F429_439xx" is selected as default project Add the following files in the project source list:
     - Utilities\STM32_EVAL\STM324x9I_EVAL\stm324x9i_eval.c
                 
 - Rebuild all files and load your image into target memory
 - Run the example
   
 
 */
