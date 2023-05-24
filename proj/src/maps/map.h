#ifndef __MAP_H
#define __MAP_H

#include <lcom/lcf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../drivers/graphics/graphics.h"
#include "../sprites/sprite.h"
#include "../xpm/floor.xpm"
#include "../xpm/wall1.xpm"

#define MAPS_PATH "/home/lcom/labs/shared/proj/src/maps/map"
#define MAPS_EXT ".txt"
#define TILE_SIZE 32

typedef struct {
    int x, y;
    uint32_t rows, columns;
    char* map;
} Map;

Map* map1;


Map* (create_map)(int level);
int (load_maps)();
int (draw_map)(Map* map);

#endif
