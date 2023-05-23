#include "map.h"
#include "../drivers/graphics/graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "maps.c"
#include <lcom/lcf.h>

// ...
extern Map * map1;


Map* (create_Map)(char *map_, int rows, int colums){
  
    Map* map = (Map*)malloc(sizeof(Map));
   
    map->rows=rows;
    map->colums=colums;
    map->map=map_;

    // Display the matrix
   

    // fclose(file);  // Close the file

    return map;
}

int (load_Maps)() {
    map1 = create_Map(map1_,1,3);
    if (!map1)
        return 1;

    // Rest of your code
    // ...

    return 0;
}

int (draw_map)(Map* map){
     printf("Matrix:\n");
    
    for (int i = 0; i <= map->rows; i++) {
        for (int j = 0; j < map->colums; j++) {
            printf("%c ", map->map[i*map->colums + j]);
        }
        printf("\n");
    }
    for (int i = 0; i <= map->rows; i++) {
        for (int j = 0; j < map->colums; j++) {
            printf("%c ", map->map[i*map->colums + j]);
            // if(map->map[i*map->colums + j]=='A');
            vg_draw_rectangle(10+30*i,10+30*j,30,30,0xFFFFFF);
        }
        printf("\n");
    }
    return 0;
}

