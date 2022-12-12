#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
static int k = 1;

double pi_bbp(void) {
    double sum = 47. / 15;
    double k_power = 1.;

    while (1) {
        k_power *= 1. / 16;
        int eightk = 8 * k;
        double second_part
            = (4. / (eightk + 1)) - (2. / (eightk + 4)) - (1. / (eightk + 5)) - (1. / (eightk + 6));
        if ((k_power * second_part) <= EPSILON) {
            break;
        } else {
            sum += k_power * second_part;
            k++;
        }
    }
    return (sum);
}

int pi_bbp_terms(void) {
    return (k);
}
