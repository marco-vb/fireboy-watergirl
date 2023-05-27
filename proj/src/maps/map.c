#include <lcom/lcf.h>

#include "map.h"

extern Map* map1;


Map* (create_map)(int level) {
    char* path = (char*)malloc(200 * sizeof(char));
    char* level_str = (char*)malloc(10 * sizeof(char));

    sprintf(path, MAPS_PATH);
    sprintf(level_str, "%d", level);
    strcat(path, level_str);
    strcat(path, MAPS_EXT);

    //sprintf(path, "/home/lcom/labs/shared/proj/src/maps/map%d.txt", level);
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
        //fscanf(file, "%c", &c); // Read the \n
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
    unsigned int background = 0;
    unsigned int wall = 0;
    unsigned int lava = 0;
    unsigned int water = 0;
    unsigned int rope_count = 0;
    unsigned int falling_block_count = 0;

    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            uint32_t index = i * map->columns + j;
            uint32_t x = map->x + j * TILE_SIZE, y = map->y + i * TILE_SIZE;

            if (map->map[index] == 'B' || map->map[index] == 'R') {
                switch (background % 3)
                {
                case 0:
                    draw_xpm((xpm_map_t)level_background1_xpm, x, y);
                    break;
                case 1:
                    draw_xpm((xpm_map_t)level_background2_xpm, x, y);
                case 2:
                    draw_xpm((xpm_map_t)level_background3_xpm, x, y);
                default:
                    draw_xpm((xpm_map_t)level_background1_xpm, x, y);
                    break;
                }
                background++;

                if (map->map[index] == 'R') {
                    int i = 0;
                    while (map->map[index] == 'R') {
                        map->map[index] = 'B';
                        ropes[rope_count][i++] = create_sprite((xpm_map_t)rope_xpm, x, y, 0, 0);
                        index += map->columns;
                        y += TILE_SIZE;
                    }

                    /* Falling Block */
                    if (map->map[index] == 'X') {
                        map->map[index] = 'B';
                        Sprite* block = create_sprite((xpm_map_t)falling_block_xpm, x, y, 0, 0);
                        Sprite* rope = ropes[rope_count][i - 1];
                        Falling_Block* falling_block = (Falling_Block*)malloc(sizeof(Falling_Block));
                        falling_block->sprite = block;
                        falling_block->rope = rope;
                        blocks[falling_block_count++] = falling_block;
                    }

                    rope_count++;
                    continue;
                }
            }
            if (map->map[index] == 'A') {
                switch (wall % 2)
                {
                case 1:
                    draw_xpm((xpm_map_t)wall1_xpm, x, y);
                    break;

                default:
                    draw_xpm((xpm_map_t)wall2_xpm, x, y);
                    break;
                }
                wall++;
            }
            if (map->map[index] == 'L') {
                if (lava % 5 == 0)draw_xpm((xpm_map_t)lava1_xpm, x, y);
                else if (lava % 5 == 4)draw_xpm((xpm_map_t)lava3_xpm, x, y);
                else draw_xpm((xpm_map_t)lava2_xpm, x, y);
                lava++;
            }
            if (map->map[index] == 'P') {
                if (water % 5 == 0)draw_xpm((xpm_map_t)water1_xpm, x, y);
                else if (water % 5 == 4)draw_xpm((xpm_map_t)water3_xpm, x, y);
                else draw_xpm((xpm_map_t)water2_xpm, x, y);
                water++;
            }
        }
        draw_background();
    }
    return 0;
}
