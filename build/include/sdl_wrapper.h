#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "config.h"
#include "sorting_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// SDL audio struct
struct SDLaudio {
    SDL_AudioSpec spec;
    Uint8 *buffer;
    Uint32 length;
    SDL_AudioDeviceID device;
    SDL_AudioStream *stream;
};

bool sdl_init(struct SortingAlgorithm *prog, struct SDLaudio *audio);
void sdl_free(struct SortingAlgorithm *prog, struct SDLaudio *audio);
void array_init(struct SortingAlgorithm *prog);
void sdl_events(struct SortingAlgorithm *prog);

#endif
