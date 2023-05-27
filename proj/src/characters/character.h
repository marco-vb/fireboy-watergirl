#ifndef __CHARECTER_H
#define __CHARECTER_H

#include <lcom/lcf.h>

#include "../drivers/graphics/graphics.h"
#include "../sprites/falling_block.h"
#include "../sprites/sprite.h"
#include "../maps/map.h"

#include "../xpm/zeldas/fireZelda/running_down_shield0.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield1.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield2.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield3.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield4.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield5.xpm"
#include "../xpm/zeldas/fireZelda/shield_left/left_shield6.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right1.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right2.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right3.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right4.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right5.xpm"
#include "../xpm/zeldas/fireZelda/shield_right/shield_right6.xpm"
#include "../xpm/zeldas/waterZelda/running_down_shield0.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield1.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield2.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield3.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield4.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield5.xpm"
#include "../xpm/zeldas/waterZelda/shield_left/left_shield6.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right1.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right2.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right3.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right4.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right5.xpm"
#include "../xpm/zeldas/waterZelda/shield_right/shield_right6.xpm"


enum Direction { LEFT, RIGHT, UP, DEFAULT };
enum Elements { FIRE, WATER };
#define GRAVITY 1
#define DEFAULT_SPEED 7
#define JUMP 15
#define CHECKBOX_PADDING 10

typedef struct {
    enum Direction direction;
    int animation_delay;
    int frames_to_next_change;
    int current_sprite;
    Sprite* sprite;
    uint32_t* left[6];
    uint32_t* right[6];
    uint32_t* front;
    enum Elements element;
} Character;

Character* fireboy, * watergirl;
extern Map* map1;
extern Falling_Block* blocks[10];

int hit_ground(Sprite* block);
void draw_falling_blocks();
void erase_blocks();

char get_tile(Map* map, u_int32_t x, u_int32_t y);
int wall_down(Character* character);
int wall_left(Character* character);
int wall_right(Character* character);
int wall_up(Character* character);
int door_fire(Character* character);
int door_water(Character* character);

int(draw_character)(Character* Character);
int (create_characters)();
int (set_position)(Character* Character, int x, int y);
void (character_current_sprite)(Character* character);
int (is_on_ground)(Character* character);
void update_character(Character* character);
int (update_direction)(Character* character, enum Direction dir);

/* Movements due to 'gravity' */
void move(Character* Character);

/* Movements due to user input */
void (move_left)(Character* Character);
void (move_right)(Character* Character);
void (jump)(Character* Character);

/* 'Cancel' movement when user releases key */
void (stop_moving)(Character* Character);
int on_fire(Character* character);
int on_water(Character* character);

#endif /* __SPRITE_H */
