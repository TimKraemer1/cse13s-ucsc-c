#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//function implementation for making print statements look cleaner
void printstatement(double approx, double lib_val, char *aname, char *lib_const) {
    printf("%s = %16.15lf, %s = %16.15lf, diff = %16.15lf\n", aname, approx, lib_const, lib_val,
        absolute(approx - lib_val));
}

//function implementation for making term printing look cleaner
void termprint(int terms, char *term_name) {
    printf("%s = %d\n", term_name, terms);
}

//this getopt code block was taken from the assignment document
#define OPTIONS "aebmrvnsh"
int main(int argc, char **argv) {
    int is_a, is_e, is_b, is_m, is_r, is_v, is_n, is_s, is_h;
    double e_value = e();
    double madhava_value = pi_madhava();
    double viete_value = pi_viete();
    double bbp_value = pi_bbp();
    double euler_value = pi_euler();
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': is_a = 1; break;
        case 'e': is_e = 1; break;
        case 'b': is_b = 1; break;
        case 'm': is_m = 1; break;
        case 'r': is_r = 1; break;
        case 'v': is_v = 1; break;
        case 'n': is_n = 1; break;
        case 's': is_s = 1; break;
        case 'h': is_h = 1; break;
        }
    }

    //print help option for -h
    if (is_h == 1) {
        printf("SYNOPSIS\nA test harness for the small numerical library.\n\nUSAGE\n./mathlib-test "
               "[-aebmrvnsh]\n\nOPTIONS\n-a   Runs all tests.\n-e   Runs e test.\n-b   Runs BBP pi "
               "test.\n-m   Runs Madhava pi test.\n-r   Runs Euler pi test.\n-v   Runs Viete pi "
               "test.\n-n   Runs Newton square root tests.\n-s   Print verbose statistics.\n-h   "
               "Display program synopsis and usage.\n");
    }

    //print e approximation for -e & if -s print number of terms
    if (is_e == 1) {
        printstatement(e_value, M_E, "e()", "M_E");
        if (is_s == 1) {
            termprint(e_terms(), "e() terms");
        }
    }

    //print pi_bbp approximation for -b & if -s print number of terms
    if (is_b == 1) {
        printstatement(bbp_value, M_PI, "pi_bbp()", "M_PI");
        if (is_s == 1) {
            termprint(pi_bbp_terms(), "pi_bbp() terms");
        }
    }

    //print pi_madhava approximation for -m & if -s print number of terms
    if (is_m == 1) {
        printstatement(madhava_value, M_PI, "pi_madhava()", "M_PI");
        if (is_s == 1) {
            termprint(pi_madhava_terms(), "pi_madhava() terms");
        }
    }

    //print pi_euler approximation for -r & if -s print number of terms
    if (is_r == 1) {
        printstatement(euler_value, M_PI, "pi_euler()", "M_PI");
        if (is_s == 1) {
            termprint(pi_euler_terms(), "pi_euler() terms");
        }
    }

    //print pi_viete approximation for -v & if -s print number of terms
    if (is_v == 1) {
        printstatement(viete_value, M_PI, "pi_viete()", "M_PI");
        if (is_s == 1) {
            termprint(pi_viete_factors(), "pi_viete() terms");
        }
    }

    //print squareroots of zero to ten in .one increments and compares them to math library sqrt function
    if (is_n == 1) {
        for (double i = 0.; i <= 10.; i += 0.1) {
            printf("sqrt_newton(%2.6lf) = %16.15lf, sqrt(%2.6lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            if (is_s == 1) {
                termprint(sqrt_newton_iters(), "newton() terms");
            }
        }
    }

    //print all tests for -a and number of terms if -s
    if (is_a == 1) {
        printstatement(e_value, M_E, "e()", "M_E");
        if (is_s == 1) {
            termprint(e_terms(), "e() terms");
        }

        printstatement(euler_value, M_PI, "pi_euler()", "M_PI");
        if (is_s == 1) {
            termprint(pi_euler_terms(), "pi_euler() terms");
        }

        printstatement(bbp_value, M_PI, "pi_bbp()", "M_PI");
        if (is_s == 1) {
            termprint(pi_bbp_terms(), "pi_bbp() terms");
        }

        printstatement(madhava_value, M_PI, "pi_madhava()", "M_PI");
        if (is_s == 1) {
            termprint(pi_madhava_terms(), "pi_madhava() terms");
        }

        printstatement(viete_value, M_PI, "pi_viete()", "M_PI");
        if (is_s == 1) {
            termprint(pi_viete_factors(), "pi_viete() terms");
        }

        for (double i = 0.; i <= 10.; i += 0.1) {
            printf("sqrt_newton(%2.6lf) = %16.15lf, sqrt(%2.6lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            if (is_s == 1) {
                termprint(sqrt_newton_iters(), "newton() terms");
            }
        }
    }
    return 0;
}
