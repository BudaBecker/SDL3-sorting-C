/*
 *   Heavily inspired by and based on the SDL3 guide from Programming Rainbow.
 *   Source: https://github.com/ProgrammingRainbow/Beginners-Guide-to-SDL3-in-C
 *
 *   Also inspired by https://www.youtube.com/@HirschDaniel
 */

#include "bubble_sort.h" // Change this to whatever sort algorithm
#include "config.h"
#include "render.h"
#include "sdl_wrapper.h"
#include "sorting_algorithm.h"
#include <SDL3/SDL_main.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Set the initial conditions
    struct SortingAlgorithm prog = {0};
    prog.is_running = true;
    prog.sorting_complete = false;
    prog.iterations = 0;
    prog.pivot = 0;
    prog.swapped = false;
    prog.comparing_pivot = -1;
    prog.sorted_until_idx = ARRAY_SIZE;

    // Start SDL
    if (!sdl_init(&prog)) {
        sdl_free(&prog);
        return EXIT_FAILURE;
    }

    // Main loop
    while (prog.is_running && !prog.sorting_complete) {
        sdl_events(&prog);
        sorting_iteration(&prog);
    }

    // End animation
    render(&prog);
    final_animation(&prog);

    // Close and Free memory
    sdl_free(&prog);
    return EXIT_SUCCESS;
}
