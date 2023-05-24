#ifndef __COUNT_DOWN_H
#define __COUNT_DOWN_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"
#include "../xpm/numbers/0.xpm"
#include "../xpm/numbers/1.xpm"
#include "../xpm/numbers/2.xpm"
#include "../xpm/numbers/3.xpm"
#include "../xpm/numbers/4.xpm"
#include "../xpm/numbers/5.xpm"
#include "../xpm/numbers/6.xpm"
#include "../xpm/numbers/7.xpm"
#include "../xpm/numbers/8.xpm"
#include "../xpm/numbers/9.xpm"


int(start_counter)(int time);
int(decrement_counter)();
int(set_timer_pos)(int x, int y);
int(draw_counter)();
int(clear_timer)();


#endif
