/*
 * ST7735Hal.h
 *
 *  Created on: Feb 10, 2023
 *      Author: setho
 */

#ifndef INC_ST7735HAL_H_
#define INC_ST7735HAL_H_

#include <stdint.h>

#define LOW 0
#define HIGH 1
#define OUTPUT 1
typedef unsigned char * PGM_P;
#define PSTR

enum {
	CS,
	DC,
	RST
};

void SPI_begin();
void SPI_transfer(uint8_t d);
void delay(int t);

void pinMode(int, int);

void digitalWrite(int pin, int state);

uint8_t pgm_read_byte(const uint8_t *a);

int random_up_to(int a);

#endif /* INC_ST7735HAL_H_ */
