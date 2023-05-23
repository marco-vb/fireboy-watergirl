#include "map.h"
#include "../drivers/graphics/graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "maps.c"
#include <lcom/lcf.h>
#include "../drivers/graphics/graphics.h"

// ...
extern Map * map1;


Map* (create_Map)(char *map_, int rows, int colums,int x, int y){
  
    Map* map = (Map*)malloc(sizeof(Map));
   
    map->rows=rows;
    map->colums=colums;
    map->map=map_;
    map->x=x;
    map->y=y;

    // Display the matrix
   

    // fclose(file);  // Close the file

    return map;
}

int (load_Maps)() {
    map1 = create_Map(map1_,10,20,100,100);
    if (!map1)
        return 1;

    // Rest of your code
    // ...

    return 0;
}

int (draw_map)(Map* map){
    
    for (int i = 0; i <= map->rows; i++) {
        for (int j = 0; j < map->colums; j++) {
            // printf("%c ", map->map[i*map->colums + j]);
            if(map->map[i*map->colums + j]=='B')
                draw_xpm((xpm_map_t)floor_xpm,map->x+j*32,map->y+i*32);
            else if(map->map[i*map->colums + j]=='A')
                draw_xpm((xpm_map_t)wall_xpm,map->x+j*32,map->y+i*32);
        }   
        draw_background();
        
    }
    return 0;
}

