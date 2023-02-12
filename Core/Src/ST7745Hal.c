/*
 * ST7745Hal.c
 *
 *  Created on: Feb 10, 2023
 *      Author: setho
 */

#include <stdlib.h>
#include <stdio.h>
#include "ST7735Hal.h"
#include "stm32f0xx_hal.h"
//#include "stm32f0xx_hal_def.h"
extern SPI_HandleTypeDef hspi1;

void digitalWrite(int pin, int state)
{
	switch (pin)
	{
	case CS:
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, state);
		 break;
	case DC:
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, state);
		 break;
	case RST:
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, state);
		 break;
	};
}

int random_up_to(int a)
{
	return rand()%a;
}

uint8_t pgm_read_byte(const uint8_t *a)
{
	return *a;
}

void pinMode(int a, int b)
{
	// already done in MSP
}

void SPI_begin()
{
}

int ctr = 0;

int get_ctr()
{
	int rc = ctr;
	ctr=0;
	return rc;
}
void SPI_transfer(uint8_t *d, int len)
{
	ctr++;
	if (HAL_OK!=HAL_SPI_Transmit(&hspi1, d, len, 10))
	{
		printf("Failed HAL_SPI_Transmit\n");
	}
//	HAL_Delay(1);
}

void delay(int ms)
{
	HAL_Delay(ms);
}

