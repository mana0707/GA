#include <stdio.h>
#include "map.h"
#include "genetic_algorithm.h"

int main(void)
{
    printf("\n");
    // マップの作製
    printf("start\n");
    Map map = map_init();
    map_print(&map);
    map_free(&map);
    printf("end\n");
    return 0;
}