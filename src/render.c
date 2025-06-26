#include "render.h"

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
