#ifndef MAP
#define MAP

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const int cost[3][2] = {{1, 2}, {3, 4}, {5, 6}};

typedef struct map
{
    int **cost;
} Map;

Map map_init()
{
    printf("map initialize start\n");
    Map map;
    map.cost = (int **)malloc(3 * sizeof(int *));
    if (map.cost == NULL)
        exit(1);
    for (int i = 0; i < 3; ++i)
    {
        map.cost[i] = (int *)malloc(2 * sizeof(int));
        if (map.cost[i] == NULL)
            exit(1);
        for (int j = 0; j < 2; ++j)
        {
            map.cost[i][j] = cost[i][j];
        }
    }
    printf("map initialize\n");
    return map;
}

int map_free(Map *map)
{
    printf("map free\n");
    if (map == NULL)
        return 1;
    for (int i = 0; i < 3; ++i)
    {
        free(map->cost[i]);
    }
    free(map->cost);
    map->cost = NULL;
    return 0;
}

int map_print(Map *map)
{
    printf("map print\n");
    if (map == NULL)
        return 1;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            printf("%d ", map->cost[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#endif
