/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
    //VCP
    PA_10,  //D0 - VCP RX
    PA_9,   //D1 - VCP TX
    
    //IO PIN Head
    PA_8,   //D2    - A0 - GPIO0,Servo1
    PA_7,   //D3    - A1 - GPIO1,Servo2
    PA_6,   //D4    - A2 - GPIO2,
    PA_5,   //D5    - A3 - GPIO3,Sens1
    PA_3,   //D6    - A4 - GPIO4,Sens2
    PA_2,   //D7    - A5 - GPIO5,Sens3
    PA_1,   //D8    - A6 - GPIO6,Sens4
    PB_2,   //D9    - GPIO7
    PB_8,   //D10   - CAN RX,I2C SCL,Servo3
    PB_9,   //D11   - CAN TX,I2C SDA,Servo4
    
    //Builtin IF
    PA_12,  //D12   - SW
    PA_11,  //D13   - LED
    
    //Motor Driver
    PA_15,  //D14   - AIN1 1
    PB_3,   //D15   - AIN2 1
    PB_10,  //D16   - BIN1 1
    PB_11,  //D17   - BIN2 1
    PB_4,   //D18   - AIN1 2
    PB_5,   //D19   - AIN2 2
    PB_0,   //D20   - BIN1 2
    PB_1,   //D21   - BIN2 2
    PB_7,   //D22   - MSLEEP
    PB_6,   //D23   - MFAULT
    PA_4,   //D24   - DAC
    
    //IMU ISP
    PB_12,  //D25 - SPI NSS
    PB_15,  //D26 - SPI MOSI
    PB_14,  //D27 - SPI MISO
    PB_13,  //D28 - SPI SCK
    
    //Battery Voltage ADC
    PA_0,   //D29 - A7 - VBAT
};

// Analog (Ax) pin number array

const uint32_t analogInputPin[] = {
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    29
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


WEAK void initVariant(void)
{
  /* In DISCO_F413ZH board, Arduino connector and Wifi embeded module are sharing the same SPI pins */
  /* We need to set the default SPI SS pin for the Wifi module to the inactive state i.e. 1 */
  /* See board User Manual: WIFI_SPI_CS = PG_11*/
    /*
  __HAL_RCC_GPIOG_CLK_ENABLE();
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);
  */
    //HAL_GPIO_Init(GPIO)
  //pinMode(12, INPUT_PULLUP);
}
    
/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
}

#ifdef __cplusplus
}
#endif
