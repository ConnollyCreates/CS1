#include <stdio.h>

#define NUM_FAMILY 3
#define MIN_COZINESS -1000
#define MAX_COZINESS 1000
#define MAX_CATS 15

int initialCoziness[MAX_CATS][NUM_FAMILY];
int cozinessChange[MAX_CATS][MAX_CATS];




int recurse(int x) {
    printf("I love c");
}

int main() {


//scans in input 
int numCats;
scanf("%d", &numCats);

   for (int i = 0; i < numCats; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &initialCoziness[i][j]);
        }
    }

    for (int i = 0; i < numCats; ++i) {
        for (int j = 0; j < numCats; ++j) {
            scanf("%d", &cozinessChange[i][j]);
        }
    }

    
    return 0;
}