#include "insertion_sort.h"

void sorting_iteration(struct SortingAlgorithm *prog, struct SDLaudio *audio) {
    // A single iteration of a insertion sort algorithm

    if (prog->sorting_complete) {
        render(prog);
        return;
    }

    if (prog->iterations < ARRAY_SIZE) {

        // Render the pair being compared (pivot vs pivot-1)
        prog->comparing_pivot = prog->pivot - 1;
        render(prog);

        // While the left neighbour is larger, shift it one to the right
        if (prog->pivot > 0 &&
            prog->array[prog->pivot] < prog->array[prog->pivot - 1]) {
            int tmp = prog->array[prog->pivot];
            prog->array[prog->pivot] = prog->array[prog->pivot - 1];
            prog->array[prog->pivot - 1] = tmp;

            // keep walking left inside the sorted prefix
            prog->pivot--;
            render(prog);
        } else {
            // Item is in place – advance to next outer element
            prog->sorted_until_idx = prog->iterations;
            prog->iterations++;
            prog->pivot = prog->iterations;
            prog->comparing_pivot = -1;
            render(prog);
        }
    } else {
        // All elements inserted
        prog->sorting_complete = true;
        prog->sorted_until_idx = ARRAY_SIZE - 1;
        prog->comparing_pivot = -1;
    }
    pop_sound(prog, audio, prog->pivot);
}
