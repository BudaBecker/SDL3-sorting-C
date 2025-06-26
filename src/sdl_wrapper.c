#include "sdl_wrapper.h"

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

void sdl_events(struct SortingAlgorithm *prog) {
    // SDL event handling (for this program only for closing the window)

    while (SDL_PollEvent(&prog->event)) {
        if (prog->event.type == SDL_EVENT_QUIT) {
            prog->is_running = false;

        } else if (prog->event.type == SDL_EVENT_KEY_DOWN) {
            if (prog->event.key.scancode == SDL_SCANCODE_ESCAPE) {
                prog->is_running = false;
            }
        }
    }
}
