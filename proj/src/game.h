#ifndef __GAME_H
#define __GAME_H

#include <lcom/lcf.h>
#include <stdint.h>

#include "drivers/timer/timer.h"
#include "drivers/kbc/kbc.h"
#include "drivers/kbc/keyboard.h"
#include "drivers/kbc/mouse.h"
#include "drivers/graphics/graphics.h"
#include "sprites/sprite.h"

extern mouse_packet_t mouse_packet;
extern keyboard_packet_t keyboard_packet;
extern Sprite* background;
extern Sprite* cursor;
extern Sprite* logo;

int game_init();
int game_loop();
int game_exit();

#endif /* __GAME_H */
