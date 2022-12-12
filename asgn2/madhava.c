#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int k = 1;

double pi_madhava(void) {
    double sum = 1.;
    double numerator = 1.;
    while (1) {
        double third = -1. / 3;
        numerator *= third;
        int denominator = (2 * k) + 1;
        double fraction = numerator / denominator;
        if ((fraction > 0 ? fraction : -fraction) <= EPSILON) {
            break;
        } else {
            sum += (numerator / denominator);
        }
        k++;
    }
    double pi = sum * sqrt_newton(12);
    return (pi);
}

int pi_madhava_terms(void) {
    return (k);
}
