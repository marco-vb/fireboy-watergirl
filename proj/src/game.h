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
extern Sprite* background, * cursor, * logo, * play_text, * settings_text, * exit_text;
extern Sprite* play_texth, * settings_texth, * exit_texth;

typedef enum {
    MAIN_MENU,
    SETTINGS_MENU,
    GAME,
    PAUSE_MENU,
    GAME_OVER,
    EXIT,
} game_state;

int game_init();
int game_loop();
int game_exit();
int draw_screen();
int draw_main_menu();
int draw_settings_menu();
int draw_game();
int draw_pause_menu();
int draw_game_over();

#endif /* __GAME_H */
