#include <stdio.h>
#include <stdlib.h>

static int k;

double sqrt_newton(double x) {
    k = 0;
    double epsilon = 1e-15;
    double z = 0.0;
    double y = 1.0;
    while (((y - z) > 0 ? (y - z) : -(y - z)) > epsilon) {
        z = y;
        y = 0.5 * (z + x / z);
        k++;
    }
    return (y);
}

int sqrt_newton_iters(void) {
    return k;
}
