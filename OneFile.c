/*
 *   Heavily inspired by and based on the SDL3 guide from Programming Rainbow.
 *   Source: https://github.com/ProgrammingRainbow/Beginners-Guide-to-SDL3-in-C
 *
 *   Also inspired by https://www.youtube.com/@HirschDaniel
 */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define WINDOW_TITLE "Sorting Algorithm"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define ARRAY_SIZE 100
#define DELAY_MS 5

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

void draw_array(struct SortingAlgorithm *prog);
bool sdl_init(struct SortingAlgorithm *prog);
void sdl_free(struct SortingAlgorithm *prog);
void array_init(struct SortingAlgorithm *prog);
void sdl_events(struct SortingAlgorithm *prog);
void sorting_iteration(struct SortingAlgorithm *prog);
void render(struct SortingAlgorithm *prog);

int main(int argc, char *argv[]) {
    struct SortingAlgorithm prog = {0};
    prog.is_running = true;
    prog.sorting_complete = false;
    prog.iterations = 0;
    prog.pivot = 0;
    prog.swapped = false;
    prog.comparing_pivot = -1;
    prog.sorted_until_idx = ARRAY_SIZE;

    if (!sdl_init(&prog)) {
        sdl_free(&prog);
        return EXIT_FAILURE;
    }

    while (prog.is_running) {
        sdl_events(&prog);
        sorting_iteration(&prog);
    }

    sdl_free(&prog);
    return EXIT_SUCCESS;
}

void array_init(struct SortingAlgorithm *prog) {
    // Create the array and shuffles it

    for (int i = 0; i < ARRAY_SIZE; i++) {
        prog->array[i] = i + 1;
    }

    // Fisher-Yates algorithm, also known as 'Knuth shuffle'
    srand((unsigned)time(NULL));
    for (int i = ARRAY_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = prog->array[i];
        prog->array[i] = prog->array[j];
        prog->array[j] = temp;
    }
}

void sdl_events(struct SortingAlgorithm *prog) {
    // SDL event handling (for this program only for closing the window)

    while (SDL_PollEvent(&prog->event)) {
        switch (prog->event.type) {
        case SDL_EVENT_QUIT:
            prog->is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (prog->event.key.scancode == SDL_SCANCODE_ESCAPE) {
                prog->is_running = false;
            }
            break;
        default:
            break;
        }
    }
}

void sorting_iteration(struct SortingAlgorithm *prog) {
    if (prog->sorting_complete) {
        if (prog->pivot != -1) {
            // TODO:
            printf("render complete animation");
            prog->pivot = -1;
        }

        render(prog);
        return;
    }

    if (prog->iterations < ARRAY_SIZE - 1) {
        if (prog->pivot < ARRAY_SIZE - prog->iterations - 1) { // if the pivot not in the end of the unordered part of the array
            prog->comparing_pivot = prog->pivot + 1;
            render(prog);

            // Standard bubble sort swap
            if (prog->array[prog->pivot] > prog->array[prog->pivot + 1]) {
                int temp = prog->array[prog->pivot];
                prog->array[prog->pivot] = prog->array[prog->pivot + 1];
                prog->array[prog->pivot + 1] = temp;
                prog->swapped = true;
            }

            prog->pivot++;
            render(prog);

        } else {
            prog->sorted_until_idx = ARRAY_SIZE - 1 - prog->iterations; // optimization so it doest need to go through all the array (only the unordered part)

            if (!prog->swapped) {
                prog->sorting_complete = true;
                prog->sorted_until_idx = 0;
                prog->comparing_pivot = -1;

            } else {
                prog->iterations++;
                prog->pivot = 0;
                prog->comparing_pivot = -1;
                prog->swapped = false;
                render(prog);
            }
        }

    } else {
        prog->sorting_complete = true;
        prog->sorted_until_idx = 0;
        prog->comparing_pivot = -1;
    }
}

void render(struct SortingAlgorithm *prog) {
    // Display the current frame

    SDL_SetRenderDrawColor(prog->renderer, 20, 20, 30, 255); // Background
    SDL_RenderClear(prog->renderer);
    draw_array(prog);
    SDL_RenderPresent(prog->renderer);
    SDL_Delay(DELAY_MS);
}

void draw_array(struct SortingAlgorithm *prog) {
    // Calculates the bars widths and heights and display them.
    // Also set the colors for the bars, pivot and comparable_pivot

    float bar_width = (float)WINDOW_WIDTH / ARRAY_SIZE;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        float bar_height = ((float)prog->array[i] / ARRAY_SIZE) * (WINDOW_HEIGHT - 50);

        SDL_FRect bar = {
            .x = i * bar_width,
            .y = WINDOW_HEIGHT - bar_height,
            .w = bar_width,
            .h = bar_height};

        if (prog->sorting_complete) {
            SDL_SetRenderDrawColor(prog->renderer, 50, 255, 50, 255); // Set color when completed (Green)

        } else if (i == prog->pivot) {
            SDL_SetRenderDrawColor(prog->renderer, 50, 50, 255, 255); // Set pivot color (Blue)

        } else if (i == prog->comparing_pivot) {
            SDL_SetRenderDrawColor(prog->renderer, 255, 50, 50, 255); // Set comparable_pivot color (Red)

        } else {
            SDL_SetRenderDrawColor(prog->renderer, 225, 225, 225, 255); // bar std color (white)
        }

        SDL_RenderFillRect(prog->renderer, &bar); // fill the bar
    }
}

bool sdl_init(struct SortingAlgorithm *prog) {
    // SDL basic init (window and renderer), and prevents any errors when initializing

    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error initializing SDL3: %s\n", SDL_GetError());
        return false;
    }

    prog->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!prog->window) {
        fprintf(stderr, "Error Creating Window: %s\n", SDL_GetError());
        return false;
    }

    prog->renderer = SDL_CreateRenderer(prog->window, NULL);
    if (!prog->renderer) {
        fprintf(stderr, "Error Creating Renderer: %s\n", SDL_GetError());
        return false;
    }

    array_init(prog);
    return true;
}

void sdl_free(struct SortingAlgorithm *prog) {
    // Free the SDL memory

    if (prog->renderer) {
        SDL_DestroyRenderer(prog->renderer);
        prog->renderer = NULL;
    }
    if (prog->window) {
        SDL_DestroyWindow(prog->window);
        prog->window = NULL;
    }
    SDL_Quit();
    printf("\nALL CLEAN!\n\n");
}
