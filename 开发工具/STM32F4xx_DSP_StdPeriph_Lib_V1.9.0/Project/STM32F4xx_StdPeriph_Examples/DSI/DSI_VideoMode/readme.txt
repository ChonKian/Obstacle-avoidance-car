/**
  @page DSI_VideoMode example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    DSI/DSI_VideoMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Description of the DSI Video Mode example.
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

This example shows how to configure DSI peripheral in Video mode and display the result on LCD.

In this basic example the goal is to explain how to use DSI peripheral in video mode.

After DSI configuration, the data transfer is performed from FLASH memory to LCD. The LTDC is configured 
to display transferred picture using Video Mode.
(Only Layer 1 is used,more details about LTDC configuration in LTDC examples)

In this example, the image used has the following parameters:
- Size : 480 x 800 
- Color mode : RGB888 format 

How to customize the used picture:

Generate a C file using the "BmpCvtST" software Tool available under: Utilities\ST\STemWin\Software:
- Select the format High Color(565)  to use RGB565 format. 
- Select the format true color 24bpp to use RGB888 format.

Replace the table in "displayed_picture_rgbXXX.h" by the new table in the generated file .

Note :
Please ensure that your picture has same size used in the example.
JPEG format is not supported by the software Tool.

@par Directory contents
    
  -  DSI/DSI_VideoMode/system_stm32f4xx.c          STM32F4xx system clock configuration file
  -  DSI/DSI_VideoMode/stm32f4xx_conf.h            Library Configuration file
  -  DSI/DSI_VideoMode/stm32f4xx_it.c              Interrupt handlers
  -  DSI/DSI_VideoMode/stm32f4xx_it.h              Interrupt handlers header file
  -  DSI/DSI_VideoMode/main.c                      Main program
  -  DSI/DSI_VideoMode/main.h                      Main program header file
  -  DSI/DSI_VideoMode/displayed_picture_rgb565.h  Image to be displayed


@par Hardware and Software environment 
 
 - This example runs on and STM32F469xx/479xx devices.
    
  - This example has been tested with STMicroelectronics STM32469I-EVAL 
    (STM32F469xx/STM32F479xx Devices) evaluation boards and can be easily 
    tailored to any other supported device and development board.
  
  - This example has been tested with STM32469I-EVAL RevB board which includes
    the MB1166 LCD board.
 
  - To use LCD hardware back-light, a hardware and software modification should be performed as below:
     * Software update: comment the OTM8008A_BACKLIGHT_SOFTWARE define line in main.c
     * Hardware update: remove R1 resistor connected on MB1166 REVA board

@par How to use it ?

In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\STM32F4xx_StdPeriph_Templates
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
  
 
 */
 