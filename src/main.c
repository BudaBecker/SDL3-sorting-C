/*
 *   Heavily inspired by and based on the SDL3 guide from Programming Rainbow.
 *   Source: https://github.com/ProgrammingRainbow/Beginners-Guide-to-SDL3-in-C
 *
 *   Also inspired by https://www.youtube.com/@HirschDaniel
 */

#include "config.h"
#include "insertion_sort.h" // Change this to whatever sort algorithm
#include "render.h"
#include "sdl_wrapper.h"
#include "sorting_algorithm.h"
#include <SDL3/SDL_main.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Create program and audio
    struct SortingAlgorithm prog = {0};
    struct SDLaudio audio = {0};

    // Start SDL
    if (!sdl_init(&prog, &audio)) {
        sdl_free(&prog, &audio);
        return EXIT_FAILURE;
    }

    // Main loop
    while (prog.is_running && !prog.sorting_complete) {
        sdl_events(&prog);
        sorting_iteration(&prog, &audio);
    }

    // End animation
    if (prog.sorting_complete) {
        render(&prog);
        final_animation(&prog, &audio);
    }

    // Close and Free memory
    sdl_free(&prog, &audio);
    return EXIT_SUCCESS;
}
