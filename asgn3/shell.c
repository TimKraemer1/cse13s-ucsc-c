#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = log(3 + 2 * n) / log(3.); i > 0; i -= 1) {
        uint32_t gap = ((uint32_t)(pow(3., i) - 1)) / 2;
        for (uint32_t a = gap; a < n; a += 1) {
            uint32_t j = a;
            uint32_t temp = move(stats, A[a]);
            while ((j >= gap) && (cmp(stats, temp, A[j - gap]) == -1)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
