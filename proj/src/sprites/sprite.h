#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"

#include "../xpm/cursor.xpm"
#include "../xpm/background.xpm"
#include "../xpm/logo.xpm"
#include "../xpm/single_player.xpm"
#include "../xpm/single_playerh.xpm"
#include "../xpm/coop.xpm"
#include "../xpm/cooph.xpm"
#include "../xpm/exit.xpm"
#include "../xpm/exitH.xpm"
#include "../xpm/fireboy.xpm"
#include "../xpm/watergirl.xpm"
#include "../xpm/game-over.xpm"

typedef struct {
    int x, y, xspeed, yspeed;
    uint16_t width, height;
    uint32_t* map;
} Sprite;

Sprite* background, * cursor, * logo, * single_player_text, * coop_text, * exit_text;
Sprite* single_player_texth, * coop_texth, * exit_texth;
Sprite* block, * fzl;
Sprite* game_over;

Sprite* create_sprite(xpm_map_t pic, uint16_t x, uint16_t y, uint16_t xspeed, uint16_t yspeed);

int load_sprites();

int destroy_sprite(Sprite* sp);

int draw_sprite(Sprite* sp);

int erase_sprite(Sprite* sp);

#endif /* __SPRITE_H */
