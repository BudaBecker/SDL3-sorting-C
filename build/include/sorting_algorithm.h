#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "config.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

// Base struct with the algorithm variables
struct SortingAlgorithm {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool is_running;

    bool sorting_complete;
    int array[ARRAY_SIZE];
    int iterations;
    int pivot;
    bool swapped;
    int comparing_pivot;
    int sorted_until_idx;
};

#endif
