#ifndef MAP
#define MAP

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum place
{
    A,
    B,
    C
} Place;

const int8_t cost[3][2] = {{1, 2}, {3, 4}, {5, 6}};

typedef struct load
{
    int8_t cost[3][2];
    int8_t place_num;
} Load;

typedef struct map
{
    int8_t **cost;
    Load *load;
} Map;

Map map_init()
{
    printf("map initialize start\n");
    Map map;
    map.cost = (int8_t **)malloc(3 * sizeof(int8_t *));
    if (map.cost == NULL)
        exit(1);
    for (int8_t i = 0; i < 3; ++i)
    {
        map.cost[i] = (int8_t *)malloc(2 * sizeof(int8_t));
        if (map.cost[i] == NULL)
            exit(1);
        for (int8_t j = 0; j < 2; ++j)
        {
            map.cost[i][j] = cost[i][j];
        }
    }
    map.load = (Load *)malloc(sizeof(Load));
    if (map.load == NULL)
        exit(1);
    for (int8_t i = 0; i < 3; ++i)
    {
        for (int8_t j = 0; j < 2; ++j)
        {
            map.load->cost[i][j] = cost[i][j];
        }
    }
    map.load->place_num = 3;

    printf("map initialize\n");
    return map;
}

int map_free(Map *map)
{
    printf("map free\n");
    if (map == NULL)
        return 1;
    for (int8_t i = 0; i < 3; ++i)
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
    for (int8_t i = 0; i < 3; ++i)
    {
        for (int8_t j = 0; j < 2; ++j)
        {
            printf("%d ", map->cost[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#endif
