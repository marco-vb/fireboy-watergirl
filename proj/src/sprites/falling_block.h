#ifndef __FALLING_BLOCK_H__
#define __FALLING_BLOCK_H__

#include "sprite.h"
#include "../xpm/falling_block.xpm"

typedef struct {
    Sprite* sprite;
    Sprite* rope;
} Falling_Block;

Falling_Block* blocks[10];

#endif /* __FALLING_BLOCK_H__ */
