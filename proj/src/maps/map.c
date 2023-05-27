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

    sprintf(path, "/home/lcom/labs/shared/proj/src/maps/map%d.txt", level);
    FILE* file = fopen(path, "r");

    Map* map = (Map*)malloc(sizeof(Map));

    if (!file || !map) { return NULL; }
    fscanf(file, "%u %u", &map->columns, &map->rows);
    map->map = (char*)malloc(map->rows * map->columns * sizeof(char));
    map->blocks = (Block* *)malloc(map->rows * map->columns * sizeof(Block *));

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
    map->n_blocks=0;

    fclose(file);
    free(path);
    free(level_str);

    return map;
}

int (load_maps)() {
    map1= create_map(1);
    map2 = create_map(2);
    current_map= map1;

    if (!map1 || !map2) { return 1; }

    return 0;
}

int (draw_map)(Map* map) {
    unsigned int background = 0;
    unsigned int wall = 0;
    unsigned int lava = 0;
    unsigned int water = 0;

    unsigned int fire_door=0;
    unsigned int water_door=0;

    unsigned int poison = 0;

    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            uint32_t index = i * map->columns + j;
            uint32_t x = map->x + j * TILE_SIZE, y = map->y + i * TILE_SIZE;

            if (map->map[index] == 'B' || map->map[index]=='C') {
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

            if(map->map[index]=='C'){
                map->blocks[map->n_blocks]=create_block(j*32,i*32);
                map->n_blocks+=1;
            }
            if(map->map[index]=='F'){
                switch (fire_door)
                {
                case 0:
                    draw_xpm((xpm_map_t)fire_door1_xpm, x, y);
                    break;
                case 1:
                    draw_xpm((xpm_map_t)fire_door2_xpm, x, y);
                    break;
                case 2:
                    draw_xpm((xpm_map_t)fire_door3_xpm, x, y);
                    break;
                case 3:
                    draw_xpm((xpm_map_t)fire_door4_xpm, x, y);
                    break;          

                default:
                    break;
                }
                fire_door++;
            }
             if(map->map[index]=='W'){
                switch (water_door)
                {
                case 0:
                    draw_xpm((xpm_map_t)water_door1_xpm, x, y);
                    break;
                case 1:
                    draw_xpm((xpm_map_t)water_door2_xpm, x, y);
                    break;
                case 2:
                    draw_xpm((xpm_map_t)water_door3_xpm, x, y);
                    break;
                case 3:
                    draw_xpm((xpm_map_t)water_door4_xpm, x, y);
                    break;          

                default:
                    break;
                }
                water_door++;

            if(map->map[index] == 'V') {
                if (poison % 5 == 0) draw_xpm((xpm_map_t)poison1_xpm, x, y);
                else if (poison % 5 == 4) draw_xpm((xpm_map_t)poison3_xpm, x, y);
                else draw_xpm((xpm_map_t)poison2_xpm, x, y);
                poison++;

            }
        }
        }
        
    }
    draw_background();
    return 0;
}
int(draw_blocks)(Map * map){
    for(int i=0;i<map->n_blocks;i++){
        erase_sprite(map->blocks[i]->sprite);
        draw_sprite(map->blocks[i]->sprite);
    }
    return 0;
}
int  (nextLevel)(){
    if(current_map==map1){ 
        current_map= map2;
        
        return 0;
    }
    return 1;
}
