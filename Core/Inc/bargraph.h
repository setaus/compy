/*
 * bar_graph.h
 *
 *  Created on: Feb 12, 2023
 *      Author: setho
 */

#ifndef INC_BARGRAPH_H_
#define INC_BARGRAPH_H_

#include <stdbool.h>

#define TICKS_TOP 1
#define TICKS_BOTTOM 2

typedef struct
{
	int led;
	int val;
} Tick_t;

typedef struct
{
	char *name;
	int x1;
	int y1;
	int leds;
	int ys;
	int border;
	int back_col;
	int var_col;
	int tick_col;
	int bar_col;
	Tick_t *ticks;
	int num_ticks;
	int draw_ticks;
	int prev_led;
	// Private
	int xs;
	int total_leds;
} Bargraph_t;

void bargraph_init(Bargraph_t *bg);
void bargraph_set(Bargraph_t *bg, int val);


#endif /* INC_BARGRAPH_H_ */
