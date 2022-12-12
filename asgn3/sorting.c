#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqr:n:p:h"

//functions to make printing cleaner and more readable
void re_seed(int seed, uint32_t size, uint32_t *A) {
    srandom(seed);
    for (uint32_t j = 0; j < size; j++) {
        A[j] = random() & 0x3FFFFFFF;
    }
}

void print_statement(char *sort_name, uint32_t size, Stats *stats) {
    printf("%s, %u elements, %lu moves, %lu compares\n", sort_name, size, stats->moves,
        stats->compares);
}

void element_printer(uint32_t *A, uint32_t n) {
    if (n > 0) {
        int counter = 0;
        for (uint32_t i = 0; i < n; i++) {
            if (counter == 5) {
                printf("\n");
                counter = 0;
            }

            printf("%13" PRIu32, A[i]);
            counter += 1;
        }
        printf("\n");
    }
}

//main function with enumeator for different inputs
//getopt inspired by getopt used in my last assignment
int main(int argc, char **argv) {
    enum { ALL, HEAP, INSERTION, SHELL, QUICKSORT, SEED, SIZE, ELEMENTS, HELP };
    Set testset = empty_set();
    int opt;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t element = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': testset = insert_set(0, testset); break;
        case 'e': testset = insert_set(1, testset); break;
        case 'i': testset = insert_set(2, testset); break;
        case 's': testset = insert_set(3, testset); break;
        case 'q': testset = insert_set(4, testset); break;
        case 'r':
            testset = insert_set(5, testset);
            seed = atoi(optarg);
            break;
        case 'n':
            testset = insert_set(6, testset);
            size = atoi(optarg);
            break;
        case 'p':
            testset = insert_set(7, testset);
            element = atoi(optarg);
            break;
        case 'h': testset = insert_set(8, testset); break;
        }
    }

    if (element > size) {
        element = size;
    }

    if (seed > UINT_MAX || seed < 0) {
        seed = 13371453;
    }

    Stats *stats_tracker = (Stats *) malloc(sizeof(Stats));
    reset(stats_tracker);

    //initializes array to be sorted
    uint32_t *array1 = (uint32_t *) malloc(sizeof(uint32_t) * size);

    //insertion sort
    if (member_set(INSERTION, testset)) {
        re_seed(seed, size, array1);
        insertion_sort(stats_tracker, array1, size);
        print_statement("Insertion Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);
    }

    //shell sort
    if (member_set(SHELL, testset)) {
        re_seed(seed, size, array1);
        shell_sort(stats_tracker, array1, size);
        print_statement("Shell Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);
    }

    //heap sort
    if (member_set(HEAP, testset)) {
        re_seed(seed, size, array1);
        heap_sort(stats_tracker, array1, size);
        print_statement("Heap Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);
    }

    //quick sort
    if (member_set(QUICKSORT, testset)) {
        re_seed(seed, size, array1);
        quick_sort(stats_tracker, array1, size);
        print_statement("Quick Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);
    }

    //help message
    if (member_set(HELP, testset)) {
        printf("SYNOPSIS\nA collection of comparison-based sorting algorithms.\n\nUSAGE\n./sorting "
               "[-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n-h              "
               "display program help and usage.\n-a              enable all sorts.\n-e             "
               " enable Heap Sort.\n-i              enable Insertion Sort.\n-s              enable "
               "Shell Sort.\n-q              enable Quick Sort.\n-n length       specify number of "
               "array elements (default: 100).\n-p elements     specify number of elements to "
               "print (default: 100).\n-r seed         specify random seed (default: 13371453).");
    }

    //print synopsis if nothing was entered
    if (!(member_set(ALL, testset) || member_set(HEAP, testset) || member_set(INSERTION, testset)
            || member_set(SHELL, testset) || member_set(QUICKSORT, testset)
            || member_set(SEED, testset) || member_set(ELEMENTS, testset)
            || member_set(SIZE, testset) || member_set(HELP, testset))) {
        printf("Select at least 1 sort to perform.\nSYNOPSIS\nA collection of comparison-based "
               "sorting algorithms.\n\nUSAGE\n./sorting "
               "[-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n-h              "
               "display program help and usage.\n-a              enable all sorts.\n-e             "
               " enable Heap Sort.\n-i              enable Insertion Sort.\n-s              enable "
               "Shell Sort.\n-q              enable Quick Sort.\n-n length       specify number of "
               "array elements (default: 100).\n-p elements     specify number of elements to "
               "print (default: 100).\n-r seed         specify random seed (default: 13371453).");
    }

    //print all
    if (member_set(ALL, testset)) {

        re_seed(seed, size, array1);
        heap_sort(stats_tracker, array1, size);
        print_statement("Heap Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);

        re_seed(seed, size, array1);
        shell_sort(stats_tracker, array1, size);
        print_statement("Shell Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);

        re_seed(seed, size, array1);
        insertion_sort(stats_tracker, array1, size);
        print_statement("Insertion Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);

        re_seed(seed, size, array1);
        quick_sort(stats_tracker, array1, size);
        print_statement("Quick Sort", size, stats_tracker);
        element_printer(array1, element);
        reset(stats_tracker);
    }

    free(stats_tracker);
    free(array1);
}
