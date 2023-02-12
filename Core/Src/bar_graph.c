/*
 * bar_graph.c
 *
 *  Created on: Feb 12, 2023
 *      Author: setho
 */


#include "bar_graph.h"
#include "ST7735.h"
#include "stdlib.h"

void bargraph_init(Bargraph_t *bg)
{
	// Horizontal axis
	SetFore(Colour(255,255,255));
	MoveTo(bg->x1, bg->y1);
	DrawTo(bg->x1+bg->xs, bg->y1);

	// Ticks
	for (int i=0; i<bg->num_ticks; i++)
	{
		SetFore(Colour(255,255,255));
		MoveTo(bg->x1+bg->ticks[i].x, bg->y1-1);
		DrawTo(bg->x1+bg->ticks[i].x, bg->y1-3);
		int val_size=0;
		if (abs(bg->ticks[i].val)>=10)
		{
			val_size = 3;
		}
		else if (abs(bg->ticks[i].val)>=1)// single digit
		{
			val_size = 2;
		}
		else
		{
			val_size = 1;
		}
		MoveTo(bg->x1+bg->ticks[i].x-val_size*6/2, bg->y1-10);
		PlotInt(bg->ticks[i].val, true);
	}
}

void bargraph_set(int val)
{
}



