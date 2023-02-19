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
void ClearDisplay();
void DisplayOn();

//void InitDisplay();
unsigned int Colour (int r, int g, int b);
void SetFore(int f);
void SetBack(int f);

void MoveTo (int x, int y);
void DrawTo (int x, int y);
void FillRect (int w, int h);
void PlotText(PGM_P p);
void PlotInt(int n, bool plus);


//void BarChart();


#endif /* INC_ST7735_H_ */
