#ifndef __COUNT_DOWN_H
#define __COUNT_DOWN_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"


int(start_counter)(int time);
int(decrement_counter)();
int(set_timer_pos)(int x, int y);
int(draw_counter)();
int(clear_timer)();


#endif
