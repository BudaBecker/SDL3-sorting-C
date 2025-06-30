#ifndef RENDER_H
#define RENDER_H

#include "config.h"
#include "sdl_wrapper.h"
#include "sorting_algorithm.h"

void draw_array(struct SortingAlgorithm *prog);
void render(struct SortingAlgorithm *prog, struct SDLaudio *audio);
void pop_sound(struct SortingAlgorithm *prog, struct SDLaudio *audio, int piv);
void final_animation(struct SortingAlgorithm *prog, struct SDLaudio *audio);

#endif
