#ifndef __MAP_H
#define __MAP_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"
#include "../xpm/floor.xpm"
#include "../xpm/wall1.xpm"



typedef struct {

    uint16_t rows, colums;
    char* map;
    int x,y;
} Map;

Map* map1;


Map* (create_Map)(char *map_, int rows, int colums,int x,int y);

int (load_Maps)();

int (draw_map)(Map* map);



#endif
