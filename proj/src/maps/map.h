#ifndef __MAP_H
#define __MAP_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"
#include "../sprites/sprite.h"
#include "../xpm/floor.xpm"
#include "../xpm/wall1.xpm"

#define MAPS_PATH "/home/lcom/labs/shared/proj/src/maps/map"
#define MAPS_EXT ".txt"
#define TILE_SIZE 32

enum Direction { LEFT, RIGHT, UP, DEFAULT };

typedef struct {
    enum Direction direction;
    int animation_delay;
    int frames_to_next_change;
    int current_sprite;
    Sprite* sprite;
    uint32_t* left[6];
    uint32_t* right[6];
    uint32_t* front;
} Character;


Character* fireboy, * watergirl;

typedef struct {
    int x, y;
    uint32_t rows, columns;
    char* map;
} Map;

Map* map1;


Map* (create_map)(int level);
int (load_maps)();
int (draw_map)(Map* map);
char get_tile(Map* map, u_int32_t x, u_int32_t y);
int wall_down(Character* character);
int wall_left(Character* character);
int wall_right(Character* character);
int wall_up(Character* character);

#endif
