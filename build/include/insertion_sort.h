#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "config.h"
#include "render.h"
#include "sorting_algorithm.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>

void sorting_iteration(struct SortingAlgorithm *prog, struct SDLaudio *audio);

#endif
