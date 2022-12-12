#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int k;

double pi_viete(void) {
    double sum = sqrt_newton(2) / 2;
    double numerator = sqrt_newton(2);
    k = 1;
    while (1) {
        double i = numerator;
        numerator = sqrt_newton(2 + i);
        if ((numerator / 2.) - (i / 2.) <= EPSILON) {
            break;
        } else {
            sum *= numerator / 2;
            k++;
        }
    }
    return (2 / sum);
}

int pi_viete_factors(void) {
    return (k);
}
