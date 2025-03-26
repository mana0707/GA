#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "map.h"

typedef struct individual {
    Place location;
    int8_t all_cost;
} Individual;

Individual individual_init(Place location, int8_t all_cost) {
    Individual individual;
    individual.location = location;
    individual.all_cost = all_cost;
    return individual;
}

#endif
