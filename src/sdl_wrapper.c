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

bool sdl_init(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
    // SDL basic init (window and renderer), and prevents any errors when initializing

    // program and audio initial conditions
    prog->is_running = true;
    prog->sorting_complete = false;
    prog->iterations = 0;
    prog->pivot = 0;
    prog->swapped = false;
    prog->comparing_pivot = -1;
    prog->sorted_until_idx = ARRAY_SIZE;
    audio->freq = 1.0;

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

    if (!SDL_LoadWAV("assets/pop.wav", &audio->spec, &audio->buffer, &audio->length)) {
        fprintf(stderr, "Error loading pop.wav: %s\n", SDL_GetError());
        return false;
    }

    audio->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio->spec, NULL, NULL);
    if (!audio->stream) {
        fprintf(stderr, "Error creating audio stream: %s", SDL_GetError());
        return false;
    }

    audio->device = SDL_GetAudioStreamDevice(audio->stream);

    array_init(prog);
    return true;
}

void sdl_free(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
    // Free the SDL memory

    // program
    if (prog->renderer) {
        SDL_DestroyRenderer(prog->renderer);
        prog->renderer = NULL;
    }
    if (prog->window) {
        SDL_DestroyWindow(prog->window);
        prog->window = NULL;
    }

    // audio
    if (audio->stream) {
        SDL_DestroyAudioStream(audio->stream);
        audio->stream = NULL;
    }
    if (audio->device) {
        SDL_PauseAudioDevice(audio->device);
        SDL_CloseAudioDevice(audio->device);
        audio->device = 0;
    }
    if (audio->buffer) {
        SDL_free(audio->buffer);
        audio->buffer = NULL;
    }

    SDL_Quit();
    printf("\nALL CLEAN!\n\n");
}

void sdl_events(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
    // SDL event handling (for this program only for closing the window)

    while (SDL_PollEvent(&prog->event)) {
        if (prog->event.type == SDL_EVENT_QUIT) {
            prog->is_running = false;

        } else if (prog->event.type == SDL_EVENT_KEY_DOWN) {
            if (prog->event.key.scancode == SDL_SCANCODE_ESCAPE) {
                prog->is_running = false;
            }
            if (prog->event.key.scancode == SDL_SCANCODE_SPACE && !prog->event.key.repeat) {
                SDL_SetAudioStreamFrequencyRatio(audio->stream, audio->freq);
                SDL_ClearAudioStream(audio->stream);
                SDL_PutAudioStreamData(audio->stream, audio->buffer, audio->length);
                SDL_FlushAudioStream(audio->stream);
                SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio->stream));
            }
        }
    }
}
