/***************************************************
* Module name:
**
Copyright 1997 Company as an unpublished work.
* All Rights Reserved.
**
The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
**
First written on xxxxx by xxxx.
**
Module Description:
* (fill in a detailed description of the module’s
* function here).
**
**************************************************/
/* Include section
* Add all #includes here
**
**************************************************/
#include "dem16216_lcd.h"

/* Defines section
* Add all #defines here
**
**************************************************/
static GPIO_InitTypeDef  GPIO_InitStruct;
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
**
**************************************************/
void LCD__vSendCmdByte(uint8_t data);
static void LCD__vSendNibble(uint8_t data);
void LCD__vSendChar(uint8_t data);
/**************************************************
* Function name : void LCD_vInit()
* returns : void
* Created by : BogTog
* Date created : 15.02.2016
* Description : Init function for executing the
*	initialisation sequence of display
* Notes : N/A
**************************************************/
void LCD_vInit()
{
	/* Enable LCD GPIO port Clock */
	LCD_GPIO_CLK_ENABLE();
	
	/* Set LCD Port pins as output */
	GPIO_InitStruct.Pin = LCD_RS_PIN | LCD_RW_PIN | LCD_EN_PIN | LCD_D4_PIN \
												| LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_GPIO_PORT, &GPIO_InitStruct);
	
	/* Begining of init sequence */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN | LCD_RW_PIN  | LCD_D4_PIN \
												| LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN, GPIO_PIN_RESET);

	/*
	HAL_Delay(40);
	LCD__vSendCmdNibble(0x2);
	LCD__vSendCmdNibble(0x2);
	LCD__vSendCmdNibble(0x8);
	HAL_Delay(1);
	LCD__vSendCmdByte(0xE);
	HAL_Delay(1);
	LCD__vSendCmdByte(0x1);
	HAL_Delay(3);
	LCD__vSendCmdByte(0x6);
	HAL_Delay(30);
	LCD__vSendCmdByte(0x62);
	*/
	HAL_Delay(40);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x2);
	LCD__vSendCmdByte(0x28);
	HAL_Delay(1);
	LCD__vSendCmdByte(0x6);
	HAL_Delay(1);
	LCD__vSendCmdByte(0x0F);
	HAL_Delay(3);
	LCD__vSendCmdByte(0x1);
	HAL_Delay(30);
	LCD__vSendCmdByte(0x14);
	LCD__vSendCmdByte(0x14);
	LCD__vSendCmdByte(0x14);
	LCD__vSendCmdByte(0x14);
}

void LCD__vSendCmdByte(uint8_t data)
{
#ifdef IF_4BIT
	/* Set low RS for instruction writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	
	LCD__vSendNibble(data & 0xF0);

	LCD__vSendNibble(data & 0xF);
	
#else
  /* Set low RS and R/W for instruction writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN | LCD_RW_PIN, GPIO_PIN_RESET);
	
	/* Set EN pin to high */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, ((data << 2) & 0x3FC), GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
#endif
}

static void LCD__vSendNibble(uint8_t data)
{
	/* Set low RS and R/W for instruction writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
	
	/* Set EN pin to high */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
		
	/* Send first nibble */
	LCD_GPIO_PORT->ODR &= 0xFF87; /* Clear port using mask */
	LCD_GPIO_PORT->ODR |= ((data & 0xF) << 3); /* Set high D4-D7 bits */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
}

void LCD__vSendChar(uint8_t data)
{
	/* Set RS high for data writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	
#ifdef IF_4BIT
	/* Set low RS for instruction writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	
	LCD__vSendNibble(data & 0xF0);

	LCD__vSendNibble(data & 0xF);
	
#else
	
#endif
}

