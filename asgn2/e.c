#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
static int k;

double e(void) {
    double sum = 1;
    k = 1;
    double fact = 1;
    while (1) {
        fact *= k;
        if (1. / fact <= EPSILON) {
            break;
        } else {
            sum += (1. / fact);
            k++;
        }
    }
    return (sum);
}

int e_terms(void) {
    return (k);
}
