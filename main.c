#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "genetic_algorithm.h"

#define POPULATION_SIZE 100
#define GENERATIONS 1000
#define MUTATION_RATE 0.1

//移動ログを元にコストの計算を行う
int calculate_cost(Individual individual, Map map) {
    int cost = 0;
    for (int i = 0; i < individual.move_log_size - 1; i++) {
        cost += map.cost[individual.move_log[i]][individual.move_log[i + 1]];
    }
    cost += map.cost[individual.move_log[individual.move_log_size - 1]][individual.move_log[0]]; // 始点に戻るコスト
    return cost;
}

//適応度を計算する
int calculate_fitness(Individual individual, int max_cost) {
    if (max_cost == 0) {
        return 0; // 最大コストが0の場合、適応度を0にする
    }
    return max_cost - individual.all_cost;
}

//突然変異
void mutate(Individual* individual, int8_t spot_size) {
    if ((double)rand() / RAND_MAX < MUTATION_RATE) {
        int index1 = rand() % individual->move_log_size;
        int index2 = rand() % individual->move_log_size;
        int8_t temp = individual->move_log[index1];
        individual->move_log[index1] = individual->move_log[index2];
        individual->move_log[index2] = temp;
    }
}

//交叉
Individual crossover(Individual parent1, Individual parent2, int8_t spot_size) {
    Individual child = individual_init_with_capacity(parent1.location, spot_size);
    int crossover_point = rand() % parent1.move_log_size;

    for (int i = 0; i < crossover_point; i++) {
        child.move_log[i] = parent1.move_log[i];
    }
    for (int i = crossover_point; i < parent2.move_log_size; i++) {
        child.move_log[i] = parent2.move_log[i];
    }
    child.move_log_size = parent1.move_log_size;
    return child;
}

//メイン処理
int run(Map map) {
    srand(time(NULL));

    Individual population[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = individual_init_with_capacity(0, map.spot_size);
        for (int j = 0; j < map.spot_size; j++) {
            population[i].move_log[j] = j;
        }
        // 経路をランダムに初期化
        for (int j = 0; j < map.spot_size; j++) {
            int index1 = rand() % map.spot_size;
            int index2 = rand() % map.spot_size;
            int8_t temp = population[i].move_log[index1];
            population[i].move_log[index1] = population[i].move_log[index2];
            population[i].move_log[index2] = temp;
        }
        population[i].move_log_size = map.spot_size;
        population[i].all_cost = calculate_cost(population[i], map);
    }

    for (int generation = 0; generation < GENERATIONS; generation++) {
        int max_cost = 0;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (population[i].all_cost > max_cost) {
                max_cost = population[i].all_cost;
            }
        }

        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i].fitness = calculate_fitness(population[i], max_cost);
        }

        Individual new_population[POPULATION_SIZE];
        for (int i = 0; i < POPULATION_SIZE; i++) {
            // 選択（ルーレット選択）
            int total_fitness = 0;
            for (int j = 0; j < POPULATION_SIZE; j++) {
                total_fitness += population[j].fitness;
            }
            int random_value1 = rand() % total_fitness;
            int random_value2 = rand() % total_fitness;
            int parent1_index = 0;
            int parent2_index = 0;
            int current_fitness = 0;
            for (int j = 0; j < POPULATION_SIZE; j++) {
                current_fitness += population[j].fitness;
                if (current_fitness > random_value1 && parent1_index == 0) {
                    parent1_index = j;
                }
                if (current_fitness > random_value2 && parent2_index == 0) {
                    parent2_index = j;
                }
            }

            // 交叉
            new_population[i] = crossover(population[parent1_index], population[parent2_index], map.spot_size);

            // 突然変異
            mutate(&new_population[i], map.spot_size);

            new_population[i].all_cost = calculate_cost(new_population[i], map);
        }

        // 新しい世代で置き換え
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = new_population[i];
        }
    }

    // 最適な経路を出力
    int best_individual_index = 0;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].all_cost < population[best_individual_index].all_cost) {
            best_individual_index = i;
        }
    }

    printf("Best path: ");
    for (int i = 0; i < map.spot_size; i++) {
        printf("%d ", population[best_individual_index].move_log[i]);
    }
    printf("\nCost: %d\n", population[best_individual_index].all_cost);

    return 0;
}

//メイン関数
int main(void) {
    // マップの作製
    int8_t* spot;
    int8_t cost_array[3][3] = {{0, 10, 15}, {10, 0, 20}, {15, 20, 0}}; // コスト行列を修正
    int8_t** cost = (int8_t**)cost_array;
    int8_t spot_array[3] = {0, 1, 2};
    spot = spot_array;
    int8_t spot_size = 3;
    int8_t cost_rows = 3;
    int8_t cost_cols = 3;
    Map map = init_map(spot, cost, spot_size, cost_rows, cost_cols);

    run(map);

    free_map(map); // マップのメモリ解放

    return 0;
}