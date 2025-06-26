#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "config.h"
#include "sorting_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool sdl_init(struct SortingAlgorithm *prog);
void sdl_free(struct SortingAlgorithm *prog);
void array_init(struct SortingAlgorithm *prog);
void sdl_events(struct SortingAlgorithm *prog);

#endif
