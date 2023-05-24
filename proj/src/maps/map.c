#include <lcom/lcf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../drivers/graphics/graphics.h"
#include "map.h"
#include "maps.c"

// ...
extern Map* map1;


Map* (create_map)(int level) {
    char* path = (char*)malloc(200 * sizeof(char));
    char* level_str = (char*)malloc(10 * sizeof(char));

    sprintf(path, MAPS_PATH);
    sprintf(level_str, "%d", level);
    strcat(path, level_str);
    strcat(path, MAPS_EXT);

    sprintf(path, "/home/lcom/labs/shared/proj/src/maps/map%d.txt", level);
    FILE* file = fopen(path, "r");

    Map* map = (Map*)malloc(sizeof(Map));

    if (!file || !map) { return NULL; }

    fscanf(file, "%u %u", &map->columns, &map->rows);
    map->map = (char*)malloc(map->rows * map->columns * sizeof(char));

    char c;
    fscanf(file, "%c", &c); // Read the \n

    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            fscanf(file, "%c", &c);

            if (c != '\n') { map->map[i * map->columns + j] = c; }
        }
        fscanf(file, "%c", &c); // Read the \n
    }

    map->x = map->y = 0;

    fclose(file);
    free(path);
    free(level_str);

    return map;
}

int (load_maps)() {
    map1 = create_map(1);

    if (!map1) { return 1; }

    // Rest of your code
    // ...

    return 0;
}

int (draw_map)(Map* map) {

    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            uint32_t index = i * map->columns + j;
            uint32_t x = map->x + j * TILE_SIZE, y = map->y + i * TILE_SIZE;

            printf("Index: %d\n", index);
            printf("X: %d\n", x);
            printf("Y: %d\n", y);

            if (map->map[index] == 'B') {
                draw_xpm((xpm_map_t)floor_xpm, x, y);
            }
            if (map->map[index] == 'A') {
                draw_xpm((xpm_map_t)wall_xpm, x, y);
            }
        }
        draw_background();
    }
    return 0;
}

