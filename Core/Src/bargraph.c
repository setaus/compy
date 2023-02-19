/*
 * bar_graph.c
 *
 *  Created on: Feb 12, 2023
 *      Author: setho
 */

#include <bargraph.h>
#include "ST7735.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LED_WIDTH 3
#define LED_PITCH (LED_WIDTH+1)

void bargraph_init(Bargraph_t *bg)
{
	bg->xs = bg->leds*LED_PITCH-1+2*bg->border;
	bg->total_leds = (bg->xs-2*bg->border+1)/LED_PITCH;
	// Background
	SetFore(Colour(0,0,0));
	MoveTo(bg->x1, bg->y1);
	FillRect(bg->xs, bg->ys);

	//
	if (bg->name)
	{

		SetFore(bg->tick_col);
		MoveTo(bg->x1-strlen(bg->name)*6-2, bg->y1+bg->ys/2-3);
		PlotText((PGM_P)bg->name);
	}
	for (int i=0; i<bg->border;i++)
	{
		// Bottom
		SetFore(bg->back_col+bg->var_col);
		MoveTo(bg->x1+i, bg->y1+i);
		DrawTo(bg->x1+bg->xs-i-1,bg->y1+i);
		// Top
		SetFore(bg->back_col-bg->var_col);
		MoveTo(bg->x1+i, bg->y1+bg->ys-i);
		DrawTo(bg->x1+bg->xs-i-1,bg->y1+bg->ys-i);
	}

	// Ticks
	for (int i=0; i<bg->num_ticks; i++)
	{
		int x = bg->x1+bg->ticks[i].led*LED_PITCH+bg->border+1;

		if (bg->draw_ticks&TICKS_TOP)
		{
			// top tick
			SetFore(bg->tick_col-bg->var_col);
			MoveTo(x, bg->y1+bg->ys);
			DrawTo(x, bg->y1+bg->ys-bg->border+1);
		}
		if (bg->draw_ticks&TICKS_BOTTOM)
		{
			// bottom tick
			SetFore(bg->tick_col+bg->var_col);
			MoveTo(x, bg->y1);
			DrawTo(x, bg->y1+bg->border-1);

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
			if (bg->draw_ticks)
			{
				SetFore(bg->tick_col);
				MoveTo(x-val_size*6/2+1, bg->y1-9); // 1 pixel gap
				PlotInt(bg->ticks[i].val, true);
			}
		}
	}
	bargraph_set(bg,-1000);
}

#define FRACTION 252

void bargraph_set(Bargraph_t *bg, int val)
{
	// convert to led number (f24.8)
	// find first led that this value is above
	int led;
	int led_frac;
	int x;

	for (x=0;x<bg->num_ticks;x++)
	{
		if (val<bg->ticks[x].val)
		{
//			printf("x=%d val=%d ticks[x].val=%d\n", x, val, bg->ticks[x].val);
			break;
		}
	}
	x--;
    if( x < 0 )
    {
         led = 0 ;
         led_frac = 0;
    }
    else if( x >= bg->num_ticks )
    {
    	printf("ceiling\n");
         led = bg->total_leds;
         led_frac = bg->total_leds*FRACTION;
    }
    else
    {
//    	printf("x=%d, bg->ticks[x].val=%d, bg->ticks[x+1].val=%d, bg->ticks[x].led=%d, bg->ticks[x+1].led=%d\n",
//    			x, bg->ticks[x].val, bg->ticks[x+1].val, bg->ticks[x].led, bg->ticks[x+1].led);
    	led = (((bg->ticks[x+1].led - bg->ticks[x].led) * (val - bg->ticks[x].val)) / (bg->ticks[x+1].val - bg->ticks[x].val)) + bg->ticks[x].led;
    	led_frac = (((bg->ticks[x+1].led * FRACTION - bg->ticks[x].led * FRACTION) * (val - bg->ticks[x].val)) / (bg->ticks[x+1].val - bg->ticks[x].val)) + bg->ticks[x].led * FRACTION;
        led++;
        led_frac+=FRACTION;
    }

	int frac = led_frac-FRACTION*(led);
	printf("val=%d level_seg=%d level_seg8=%d frac=%d\n", val, led, led_frac, frac);

	int i;
	for (i=0; i<=led && i<bg->total_leds; i++)
	{
		if (i==led)
		{
			frac = frac*frac/FRACTION;
//			printf("col %d,%d,%d\n", 4,frac+4,4);
			SetFore(Colour(4,frac+4,4));
		}
		else
		{
			SetFore(bg->bar_col);
		}
		MoveTo(bg->x1+bg->border+i*LED_PITCH, bg->y1+bg->border);
		FillRect(LED_WIDTH, bg->ys-2*bg->border+1);
	}
	for (; i<bg->total_leds;i++)
	{
		SetFore(Colour(4,4,4));
		MoveTo(bg->x1+bg->border+i*LED_PITCH, bg->y1+bg->border);
		FillRect(LED_WIDTH, bg->ys-2*bg->border+1);
	}

	// new value higher
	if (val>bg->prev_led)
	{

//		for (int i=prev_led;i<=
	}
}



