#include "bubble_sort.h"

void sorting_iteration(struct SortingAlgorithm *prog) {
    // A single iteration of a bubble sort algorithm

    if (prog->sorting_complete) {
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
