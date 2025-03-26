#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <stdint.h>

typedef struct individual
{
    /* data */
    int8_t location;
    int8_t all_cost;
} Individual;

Individual individual_init(int8_t first_location) {
    Individual individual;
    individual.location = first_location;
    individual.all_cost = 0;
    return individual;
}

#endif
