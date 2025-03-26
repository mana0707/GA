#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <stdint.h>

typedef struct individual
{
    int8_t location;
    int8_t* move_log; // Array to store the sequence of moves
    int8_t move_log_size; // Size of the move_log array
    int8_t all_cost;
    int8_t fitness;
    int8_t move_log_capacity; // Capacity of the move_log array
    int8_t genaretion;
} Individual;

Individual individual_init(int8_t first_location) {
    Individual individual;
    individual.location = first_location;
    individual.all_cost = 0;
    individual.fitness = 0;
    individual.move_log = NULL;
    individual.move_log_size = 0;
    return individual;
}

Individual individual_init_with_capacity(int8_t first_location, int8_t capacity) {
    Individual individual;
    individual.location = first_location;
    individual.all_cost = 0;
    individual.fitness = 0;
    individual.move_log = (int8_t*)malloc(capacity * sizeof(int8_t));
    individual.move_log_size = 0;
    individual.move_log_capacity = capacity;
    return individual;
}

#endif
