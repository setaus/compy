/*
 * bar_graph.h
 *
 *  Created on: Feb 12, 2023
 *      Author: setho
 */

#ifndef INC_BAR_GRAPH_H_
#define INC_BAR_GRAPH_H_

typedef struct
{
	int x;
	int val;
} Tick_t;

typedef struct
{
	int x1;
	int y1;
	int xs;
	int ys;
	Tick_t *ticks;
	int num_ticks;
	int prev;
} Bargraph_t;

void bargraph_init(Bargraph_t *bg);
void bargraph_set(int val);


#endif /* INC_BAR_GRAPH_H_ */
