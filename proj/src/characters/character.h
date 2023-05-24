#ifndef __CHARECTER_H
#define __CHARECTER_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"

#include "../sprites/sprite.h"
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

enum Direction{LEFT,RIGHT,UP,DEFAULT};

typedef struct {
    enum Direction direction;
    int animation_delay;
    int frames_to_next_change;
    int current_sprite;
    Sprite * sprite;
    uint32_t* left[6];
    uint32_t* right[6];
    uint32_t *front;
} Character;


Character* fireboy, * watergirl;


int (create_Characters)();

int (setPosition)(Character * Character, int x, int y);

void (moveLeft)(Character * Character);
void (moveRight)(Character * Character);
int(draw_character)(Character * Character);
int (jump)(Character * Character);
void (character_current_sprite)(Character * character);


#endif /* __SPRITE_H */
