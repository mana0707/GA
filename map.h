#ifndef MAP
#define MAP

#include <stdint.h>
#include <stdlib.h>
#include <string.h> // memcpyを使うために必要

typedef struct map
{
    int8_t* spot;
    int8_t** cost;
    int8_t spot_size; // spotのサイズを保持
    int8_t cost_rows; // costの行数を保持
    int8_t cost_cols; // costの列数を保持
} Map;

Map init_map(int8_t* spot_input, int8_t** cost_input, int8_t spot_size, int8_t cost_rows, int8_t cost_cols) {
    Map map;

    // spotのコピーを作成
    map.spot = (int8_t*)malloc(sizeof(int8_t) * spot_size);
    if (map.spot == NULL) {
        // メモリ確保失敗時のエラー処理
        return map; // エラーを示す値を返すなどの処理が必要
    }
    memcpy(map.spot, spot_input, sizeof(int8_t) * spot_size);

    // costのコピーを作成
    map.cost = (int8_t**)malloc(sizeof(int8_t*) * cost_rows);
    if (map.cost == NULL) {
        // メモリ確保失敗時のエラー処理
        free(map.spot); // spotのメモリを解放
        return map; // エラーを示す値を返すなどの処理が必要
    }
    for (int i = 0; i < cost_rows; i++) {
        map.cost[i] = (int8_t*)malloc(sizeof(int8_t) * cost_cols);
        if (map.cost[i] == NULL) {
            // メモリ確保失敗時のエラー処理
            for (int j = 0; j < i; j++) {
                free(map.cost[j]); // 確保済みのメモリを解放
            }
            free(map.cost);
            free(map.spot);
            return map; // エラーを示す値を返すなどの処理が必要
        }
        memcpy(map.cost[i], cost_input[i], sizeof(int8_t) * cost_cols);
    }

    map.spot_size = spot_size;
    map.cost_rows = cost_rows;
    map.cost_cols = cost_cols;

    return map;
}

void free_map(Map map) {
    if (map.spot != NULL) {
        free(map.spot);
    }
    if (map.cost != NULL) {
        for (int i = 0; i < map.cost_rows; i++) {
            free(map.cost[i]);
        }
        free(map.cost);
    }
}

#endif