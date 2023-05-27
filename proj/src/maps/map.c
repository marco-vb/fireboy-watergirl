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
    map2 = create_map(2);
    current_map = map1;

    if (!map1 || !map2) { return 1; }

    return 0;
}

int (draw_map)(Map* map) {
    unsigned int background = 0;
    unsigned int wall = 0;
    unsigned int lava = 0;
    unsigned int water = 0;
    unsigned int rope_count = 0;
    unsigned int falling_block_count = 0;

    unsigned int fire_door = 0;
    unsigned int water_door = 0;

    unsigned int poison = 0;

    for (uint32_t i = 0; i < map->rows; i++) {
        for (uint32_t j = 0; j < map->columns; j++) {
            uint32_t index = i * map->columns + j;
            uint32_t x = map->x + j * TILE_SIZE, y = map->y + i * TILE_SIZE;

            if (map->map[index] == 'B' || map->map[index] == 'R') {
                switch (background % 3)
                {
                case 0:
                    if(draw_xpm((xpm_map_t)level_background1_xpm, x, y)){
                        printf("Failed to load first image of the background\n");
                        return 1;
                    }
                    break;
                case 1:
                   if( draw_xpm((xpm_map_t)level_background2_xpm, x, y)){
                        printf("Failed to load second image of the background\n");
                        return 1;
                    }
                case 2:
                    if(draw_xpm((xpm_map_t)level_background3_xpm, x, y)){
                        printf("Failed to load third image of the background\n");
                        return 1;
                    }
                default:
                    if(draw_xpm((xpm_map_t)level_background1_xpm, x, y)){
                        printf("Failed to load fourth image of the background\n");
                        return 1;
                    }
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
                    if(draw_xpm((xpm_map_t)wall1_xpm, x, y)){
                        printf("Failed to load first image of the wall\n");
                        return 1;
                    }
                    break;

                default:
                    if(draw_xpm((xpm_map_t)wall2_xpm, x, y)){
                        printf("Failed to load second image of the wall\n");
                        return 1;
                    }
                    break;
                }
                wall++;
            }
            if (map->map[index] == 'L') {
                if (lava % 5 == 0) {
                    if(draw_xpm((xpm_map_t)lava1_xpm, x, y)){
                            printf("Failed to load first image of the lava\n");
                            return 1;
                    }
                }
                else if (lava % 5 == 4){
                    if(draw_xpm((xpm_map_t)lava3_xpm, x, y)){
                        printf("Failed to load second image of the lava\n");
                        return 1;
                    }
                }
                else{ 
                    if(draw_xpm((xpm_map_t)lava2_xpm, x, y)){
                        printf("Failed to load third image of the lava\n");
                        return 1;
                    }
                }
                lava++;
            }
            if (map->map[index] == 'P') {
                if (water % 5 == 0){
                    if(draw_xpm((xpm_map_t)water1_xpm, x, y)){
                        printf("Failed to load first image of the water\n");
                        return 1;
                    }
                }
                else if (water % 5 == 4){
                    if(draw_xpm((xpm_map_t)water3_xpm, x, y)){
                        printf("Failed to load second image of the water\n");
                        return 1;
                    }
                }
                else{ 
                    if(draw_xpm((xpm_map_t)water2_xpm, x, y)){
                        printf("Failed to load third image of the water\n");
                        return 1;
                    }
                }
                water++;
            }

            if(map->map[index]=='F'){
                switch (fire_door)
                {
                case 0:
                    if(draw_xpm((xpm_map_t)fire_door1_xpm, x, y)){
                        printf("Failed to load first image of the fire door\n");
                        return 1;
                    }
                    break;
                case 1:
                    if(draw_xpm((xpm_map_t)fire_door2_xpm, x, y)){
                        printf("Failed to load second image of the fire door\n");
                        return 1;
                    }
                    break;
                case 2:
                    if(draw_xpm((xpm_map_t)fire_door3_xpm, x, y)){
                        printf("Failed to load third image of the fire door\n");
                        return 1;
                    }
                    break;
                case 3:
                    if(draw_xpm((xpm_map_t)fire_door4_xpm, x, y)){
                        printf("Failed to load fourth image of the fire door\n");
                        return 1;
                    }
                    break;          

                default:
                    break;
                }
                fire_door++;
            }
            if (map->map[index] == 'W') {
                switch (water_door)
                {
                case 0:
                    if(draw_xpm((xpm_map_t)water_door1_xpm, x, y)){
                        printf("Failed to load first image of the water door\n");
                        return 1;
                    }
                    break;
                case 1:
                    if(draw_xpm((xpm_map_t)water_door2_xpm, x, y)){
                        printf("Failed to load second image of the water door\n");
                        return 1;
                    }
                    break;
                case 2:
                    if(draw_xpm((xpm_map_t)water_door3_xpm, x, y)){
                        printf("Failed to load third image of the water door\n");
                        return 1;
                    }
                    break;
                case 3:
                    if(draw_xpm((xpm_map_t)water_door4_xpm, x, y)){
                        printf("Failed to load fourth image of the water door\n");
                        return 1;
                    }
                    break;          

                default:
                    break;
                }
                water_door++;

            if(map->map[index] == 'V') {
                if (poison % 5 == 0) {
                    if(draw_xpm((xpm_map_t)poison1_xpm, x, y)){
                        printf("Failed to load first image of the poison\n");
                        return 1;
                    }
                    }
                else if (poison % 5 == 4){ 
                    if(draw_xpm((xpm_map_t)poison3_xpm, x, y)){
                        printf("Failed to load second image of the poison\n");
                        return 1;
                    }
                }
                else{ 
                    if(draw_xpm((xpm_map_t)poison2_xpm, x, y)){
                        printf("Failed to load third image of the poison\n");
                        return 1;
                    }
                }
                poison++;

                }
            }
        }

    }
    draw_background();
    return 0;
}

int  (nextLevel)(){
    if(current_map==map1){ 
        current_map= map2;
        return 0;
    }
    if(current_map==map2){
        current_map=map1;
        return 1;
    }
    return 1;
}
