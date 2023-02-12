/*
 * ST7735.h
 *
 *  Created on: Feb 11, 2023
 *      Author: setho
 */

#ifndef INC_ST7735_H_
#define INC_ST7735_H_

#include <stdbool.h>
#include <ST7735Hal.h>


void InitDisplay();
void MoveTo (int x, int y);
void PlotText(PGM_P p);
void SetFore(int f);
unsigned int Colour (int r, int g, int b);
void FillRect (int w, int h);
void DrawTo (int x, int y);
void PlotInt(int n, bool plus);


void setup();
void BarChart();


#endif /* INC_ST7735_H_ */
