#include "map.h"
#include "../drivers/graphics/graphics.h"

Map* (create_Map)(const char *filePath){
    printf(filePath);
    Map* map = (Map*)malloc(sizeof(Map));
    FILE *file = fopen("map1.txt", "r");  // Open the file in read mode
    if (file == NULL) {
        printf("Failed to  the file.\n");
        return NULL;
    }

    map->map=(char*)malloc(2500*sizeof(char)) ;
    int rows = 0;
    int cols = 0;
    // Read the matrix from the file
    char c;
   
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            map->colums=cols;
            rows++;
            cols = 0;
        } else if (c != ' ') {
            map->map[rows*map->colums + cols] = c;
        }
    }
    map->rows=rows;

    // Display the matrix
    printf("Matrix:\n");
    for (int i = 0; i <= map->rows; i++) {
        for (int j = 0; j < map->colums; j++) {
            printf("%c ", map->map[i*map->colums + j]);
        }
        printf("\n");
    }

    fclose(file);  // Close the file

    return map;
}

int (load_Maps)() {
    char cwd[PATH_MAX];
if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working directory: %s\n", cwd);
} else {
    printf("Failed to retrieve current working directory.\n");
}
    Map* map1 = create_Map("files/map1.txt");
    if (!map1)
        return 1;

    // Rest of your code
    // ...

    return 0;
}

