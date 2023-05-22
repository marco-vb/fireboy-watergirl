#ifndef __MAP_H
#define __MAP_H

#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"



typedef struct {

    uint16_t rows, colums;
    char* map;
} Map;

Map* map1;


Map* (create_Map)(const char *filePath);

int (load_Maps)();



#endif
