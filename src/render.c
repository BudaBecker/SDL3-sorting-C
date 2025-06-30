#include "render.h"

void render(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
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

        if (i == prog->pivot) {
            SDL_SetRenderDrawColor(prog->renderer, 50, 50, 255, 255); // Set pivot color (Blue)

        } else if (i == prog->comparing_pivot) {
            SDL_SetRenderDrawColor(prog->renderer, 255, 50, 50, 255); // Set comparable_pivot color (Red)

        } else {
            SDL_SetRenderDrawColor(prog->renderer, 225, 225, 225, 255); // bar std color (white)
        }

        SDL_RenderFillRect(prog->renderer, &bar); // fill the bar
    }
}

void pop_sound(struct SortingAlgorithm *prog, struct SDLaudio *audio, int piv) {
    float frequency;

    frequency = INIT_FREQ + (piv - 1) * (FINAL_FREQ - INIT_FREQ) / (ARRAY_SIZE - 1);

    SDL_SetAudioStreamFrequencyRatio(audio->stream, frequency);
    SDL_ClearAudioStream(audio->stream);
    SDL_PutAudioStreamData(audio->stream, audio->buffer, audio->length);
    SDL_FlushAudioStream(audio->stream);
    SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio->stream));
}

void final_animation(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
    // Progressive final animation: bars turn green one by one

    float bar_width = (float)WINDOW_WIDTH / ARRAY_SIZE;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Clear the screen
        SDL_SetRenderDrawColor(prog->renderer, 20, 20, 30, 255); // Background
        SDL_RenderClear(prog->renderer);

        // Draw all bars up to i in green, rest in white
        for (int j = 0; j < ARRAY_SIZE; j++) {
            float bar_height = ((float)prog->array[j] / ARRAY_SIZE) * (WINDOW_HEIGHT - 50);

            SDL_FRect bar = {
                .x = j * bar_width,
                .y = WINDOW_HEIGHT - bar_height,
                .w = bar_width,
                .h = bar_height};

            if (j <= i) {
                SDL_SetRenderDrawColor(prog->renderer, 50, 255, 50, 255); // Green
            } else {
                SDL_SetRenderDrawColor(prog->renderer, 225, 225, 225, 255); // White
            }
            SDL_RenderFillRect(prog->renderer, &bar);
        }

        pop_sound(prog, audio, i + 1);
        SDL_RenderPresent(prog->renderer);
        SDL_Delay(30);
    }
}
