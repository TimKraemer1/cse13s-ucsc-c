#include "names.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

//this code snippet comes from the assignment document
typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

//function created that will help later in the actual implementation of the game
int points_and_wincondition(int *parray, int pvalue, int cplayer) {
    parray[cplayer] += pvalue;
    if (parray[cplayer] >= 100) {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    //Number of Players Input

    int input = 0;
    int numplayers = 0;
    printf("How many players? ");
    scanf("%d", &input);
    if (input < 2 || input > 10) {
        fprintf(stderr, "Invalid number of players, Using 2 instead. \n");
        numplayers = 2;
    } else {
        numplayers = input;
    }

    //Seed Input

    printf("Random seed: ");
    long seedinput = 0;
    unsigned seed;
    if (scanf("%ld", &seedinput) == 0) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }

    else if (seedinput < 0 || seedinput > UINT_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    } else {
        seed = (unsigned) seedinput;
    }

    int pointsarray[numplayers];
    for (int i = 0; i < numplayers; i++) {
        pointsarray[i] = 0;
    }

    //Start of the actual game

    srandom(seed);
    int wincondition = 0;
    int currentplayer = 0;
    while (1) {
        int roll = 1;
        printf("%s rolls the pig...", names[currentplayer]);
        while (roll) {
            int randomposition = pig[random() % 7];
            if (randomposition == 1 || randomposition == 2) {
                if (randomposition == 1) {
                    printf(" pig lands on back");
                } else {
                    printf(" pig lands upright");
                }
                if (points_and_wincondition(pointsarray, 10, currentplayer) == 1) {
                    wincondition = 1;
                    break;
                }

            }

            else if (randomposition == 3) {
                printf(" pig lands on snout");
                if (points_and_wincondition(pointsarray, 15, currentplayer) == 1) {
                    wincondition = 1;
                    break;
                }
            }

            else if (randomposition == 4) {
                printf(" pig lands on ear");
                if (points_and_wincondition(pointsarray, 5, currentplayer) == 1) {
                    wincondition = 1;
                    break;
                }

            }

            else {
                printf(" pig lands on side\n");
                roll = 0;
                if (currentplayer == (numplayers - 1)) {
                    currentplayer = 0;
                } else {
                    currentplayer++;
                }
            }
        }
        if (wincondition == 1) {
            break;
        }
    }
    printf("\n%s wins with %d points!\n", names[currentplayer], pointsarray[currentplayer]);
}
