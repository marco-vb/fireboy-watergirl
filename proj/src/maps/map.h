#ifndef __MAP_H
#define __MAP_H

#include <lcom/lcf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../drivers/graphics/graphics.h"
#include "../sprites/sprite.h"
#include "../objects/block.h"
#include "../xpm/background/level_background1.xpm"
#include "../xpm/background/level_background2.xpm"
#include "../xpm/background/level_background3.xpm"
#include "../xpm/background/wall1.xpm"
#include "../xpm/background/wall2.xpm"
#include "../xpm/background/lava1.xpm"
#include "../xpm/background/lava2.xpm"
#include "../xpm/background/lava3.xpm"
#include "../xpm/background/water1.xpm"
#include "../xpm/background/water2.xpm"
#include "../xpm/background/water3.xpm"

#define MAPS_PATH "/home/lcom/labs/shared/proj/src/maps/map"
#define MAPS_EXT ".txt"
#define TILE_SIZE 32

typedef struct {
    int x, y;
    uint32_t rows, columns;
    char* map;
    Block * * blocks;
    int n_blocks;
} Map;

Map* map1;


Map* (create_map)(int level);
int (load_maps)();
int (draw_map)(Map* map);
int (update_blocks )(Map * map);
int(draw_blocks)(Map * map);

#endif
