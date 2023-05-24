#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"

#include "../xpm/cursor.xpm"
#include "../xpm/background.xpm"
#include "../xpm/logo.xpm"
#include "../xpm/play.xpm"
#include "../xpm/playH.xpm"
#include "../xpm/settings.xpm"
#include "../xpm/settingsH.xpm"
#include "../xpm/exit.xpm"
#include "../xpm/exitH.xpm"
#include "../xpm/fireboy.xpm"
#include "../xpm/watergirl.xpm"


typedef struct {
    uint16_t x, y;
    int16_t xspeed, yspeed;
    uint16_t width, height;
    uint32_t* map;
} Sprite;

Sprite* background, * cursor, * logo, * play_text, * settings_text, * exit_text;
Sprite* play_texth, * settings_texth, * exit_texth;
Sprite* block, *fzl;

Sprite* create_sprite(xpm_map_t pic, uint16_t x, uint16_t y, int16_t xspeed, int16_t yspeed);

int load_sprites();

int destroy_sprite(Sprite* sp);

int draw_sprite(Sprite* sp);

int erase_sprite(Sprite* sp);

int move_sprite(Sprite* sp);

int animate_sprite(Sprite* sp);

#endif /* __SPRITE_H */
