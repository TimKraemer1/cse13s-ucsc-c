#include "mathlib.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t k;

double pi_euler(void) {
    k = 1;
    double sum = 0.;
    while (1) {

        if ((1. / (k * k)) <= EPSILON) {
            break;
        } else {
            sum += (1. / (k * k));
            k++;
            //printf("%16.15lf\n", condition_value);
        }
    }
    double pi = sqrt_newton(sum * 6);
    return (pi);
}

int pi_euler_terms(void) {
    return ((int) k);
}
