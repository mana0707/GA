#include <stdio.h>
#include "map.h"
#include "genetic_algorithm.h"

const int8_t population_size = 100;

typedef struct world
{
    Map map;
    int population_size;
    Individual *individuals;
} World;

World world_init(Place place)
{
    World world;
    world.map = map_init();
    world.population_size = population_size;
    world.individuals = (Individual *)malloc(sizeof(Individual) * world.population_size);
    for (int i = 0; i < world.population_size; i++)
    {
        world.individuals[i] = individual_init(place,0);
    }
    return world;
}

int main(void)
{
    printf("\n");
    // マップの作製
    printf("start\n");
    World world = world_init(A);
    map_print(&world.map);
    map_free(&world.map);
    printf("end\n");
    return 0;
}
