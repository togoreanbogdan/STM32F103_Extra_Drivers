/***************************************************
* Module name: STM32F103C8T6 Board BSP
*
* Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
* First written on 10.02.2016 by BogTog.
*
* Module Description:
* General Board Support Package for minimum development
* board with STM32F103C8T6 MCU
*
***************************************************/
/* Include section */
#include "stm32f10xx_board.h"

/**************************************************
* Function name : BSP_LED_Init()
* returns : void
* Created by : BogTog
* Date created : 10.02.2016
* Description : LED GPIO Initialization function
* Notes : restrictions, odd modes
**************************************************/
void BSP_LED_Init()
{
	GPIO_InitTypeDef  gpioinitstruct = {0};

  /* Enable the GPIO_LED Clock */
  LED_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin    = LED_PIN;
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &gpioinitstruct);

  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
}

/**************************************************
* Function name : BSP_LED_On()
* returns : void
* Created by : BogTog
* Date created : 10.02.2016
* Description : LED Turn on function
* Notes : restrictions, odd modes
**************************************************/
void BSP_LED_On()
{
  /* Set PIN to switch on the LED */
  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

/**************************************************
* Function name : BSP_LED_Off()
* returns : void
* Created by : BogTog
* Date created : 10.02.2016
* Description : LED Turn off function
* Notes : restrictions, odd modes
**************************************************/
void BSP_LED_Off()
{
  /* Set PIN to switch on the LED */
  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
}

/**************************************************
* Function name : BSP_LED_Toggle()
* returns : void
* Created by : BogTog
* Date created : 10.02.2016
* Description : LED toggle function
* Notes : restrictions, odd modes
**************************************************/
void BSP_LED_Toggle()
{
  /* Set PIN to switch on the LED */
  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
}
