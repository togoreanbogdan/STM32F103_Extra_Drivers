/***************************************************
* Module name: DEM 16216 LCD Driver
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
* General driver for DEM16216 LCD display
*
***************************************************/
#ifndef __DEM16216_LCD
#define __DEM16216_LCD

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"

/* Exported types ------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define IF_4BIT	  //set interface to 4 bit

#define LCD_RS_PIN                      GPIO_PIN_0
#define LCD_RW_PIN                      GPIO_PIN_1
#define LCD_EN_PIN                      GPIO_PIN_2
#define LCD_D4_PIN                      GPIO_PIN_3
#define LCD_D5_PIN                      GPIO_PIN_4
#define LCD_D6_PIN                      GPIO_PIN_5
#define LCD_D7_PIN                      GPIO_PIN_6
	
#define LCD_GPIO_PORT                   GPIOA
#define LCD_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()  
#define LCD_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**************************************************/
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
*
***************************************************/
void LCD_vInit(void);
void LCD_vWriteCharNext(void);
void LCD_vWriteCharPos(uint8_t pos);
void LCD_vGoHome(void);
	
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */