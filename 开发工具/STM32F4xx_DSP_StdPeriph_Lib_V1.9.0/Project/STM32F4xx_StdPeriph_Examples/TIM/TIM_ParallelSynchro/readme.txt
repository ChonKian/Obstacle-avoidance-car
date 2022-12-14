/**
  @page TIM_ParallelSynchro TIM Parallel Synchro example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    TIM/TIM_ParallelSynchro/readme.txt 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Description of the TIM Parallel Synchro example.
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

This example shows how to synchronize TIM peripherals in parallel mode.
In this example three timers are used:

Timers synchronisation in parallel mode:

1/TIM2 is configured as Master Timer:
   - PWM Mode is used
   - The TIM2 Update event is used as Trigger Output 
 
2/TIM3 and TIM4 are slaves for TIM2,
   - PWM Mode is used
   - The ITR1(TIM2) is used as input trigger for both slaves 
   - Gated mode is used, so starts and stops of slaves counters are controlled 
     by the Master trigger output signal(update event).

The TIM2 counter clock is 84 MHz.
  
  The Master Timer TIM2 is running at TIM2 frequency:
  TIM2 frequency = TIM2 counter clock/ (TIM2 period + 1) = 328.125 KHz 
  and the duty cycle is equal to TIM2_CCR1/(TIM2_ARR + 1) = 25%.
  
  The TIM3 is running at:
  (TIM2 frequency)/ (TIM3 period + 1) = 32.815 KHz and a duty cycle equal to 
  TIM3_CCR1/(TIM3_ARR + 1) = 30%
  
  The TIM4 is running at:
  (TIM2 frequency)/ (TIM4 period + 1) = 65.630 KHz and a duty cycle equal to 
  TIM4_CCR1/(TIM4_ARR + 1) = 60%
  
@par Directory contents 
  
  - TIM/TIM_ParallelSynchro/system_stm32f4xx.c   STM32F4xx system clock configuration file
  - TIM/TIM_ParallelSynchro/stm32f4xx_conf.h     Library Configuration file
  - TIM/TIM_ParallelSynchro/stm32f4xx_it.c       Interrupt handlers
  - TIM/TIM_ParallelSynchro/stm32f4xx_it.h       Interrupt handlers header file
  - TIM/TIM_ParallelSynchro/main.c               Main program
  - TIM/TIM_ParallelSynchro/main.h               Main program header file

  
@par Hardware and Software environment 

  - This example runs on STM32F405xx/407xx, STM32F415xx/417xx, STM32F427xx/437xx and 
    STM32F429xx/439xx devices.
    
  - This example has been tested with STMicroelectronics STM324xG-EVAL (STM32F40xx/
    STM32F41xx Devices), STM32437I-EVAL (STM32F427xx/STM32F437xx Devices) and 
    STM324x9I-EVAL RevB (STM32F429xx/STM32F439xx Devices) evaluation boards and 
    can be easily tailored to any other supported device and development board.

  - STM324xG-EVAL/STM32437I-EVAL and STM324x9I-EVAL RevB Set-up 
    - Connect the pins to an oscilloscope to monitor the different waveforms:
      - TIM2_CH1 (PA.00)
      - TIM3_CH1 (PC.06) 
      - TIM4_CH1 (PB.06) 
  
  
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
