#include <stdio.h>
#include "map.h"
#include "genetic_algorithm.h"

int main(void){
    int8_t* spot;
    int8_t cost_array[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int8_t** cost = (int8_t**)cost_array;
    int8_t spot_array[3] = {1, 2, 3};
    spot = spot_array;
    int8_t spot_size; // spotのサイズを保持
    int8_t cost_rows; // costの行数を保持
    int8_t cost_cols; // costの列数を保持

    spot_size = 3;
    cost_rows = 3;
    cost_cols = 2;
    init_map(spot, spot_size, cost, cost_rows, cost_cols);
    return 0;
}
