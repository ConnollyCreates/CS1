
#include <stdio.h>

#define CAT   15
#define HOUSE 3
#define oo 987654321

int location[CAT];
int modification[CAT][CAT];
int initial_value[HOUSE][CAT];

int best_sum;
int best_min;
int num_cats;

void go(int index) {
    if (index == -1) {
        int count[HOUSE] = {0};
        int cozy[CAT] = {0};
        int cur_sum = 0;
        int cur_min = oo;
        for (int i = 0; i < num_cats; i++) {
            count[location[i]]++;
            cozy[i] = initial_value[location[i]][i];
            for (int j = 0; j < num_cats; j++) {
                if (location[j] == location[i]) {
                    cozy[i] += modification[i][j];
                }
            }
            cur_sum += cozy[i];
            if (cur_min > cozy[i]) {
                cur_min = cozy[i];
            }
        }
        for (int i = 0; i < HOUSE; i++) {
            if (!count[i]) return;
        }

        if (best_min < cur_min) best_min = cur_min;
        if (best_sum < cur_sum) best_sum = cur_sum;
        return;
    }

    for (int i = 0; i < HOUSE; i++) {
        location[index] = i;
        go(index - 1);
    }
}

int main() {
    best_sum = -oo;
    best_min = -oo;

    scanf("%d", &num_cats);
    for (int i = 0; i < num_cats; i++) {
        for (int j = 0; j < HOUSE; j++) {
            scanf("%d", &initial_value[j][i]);
        }
    }
    
    for (int i = 0; i < num_cats; i++) {
        for (int j = 0; j < num_cats; j++) {
            scanf("%d", &modification[i][j]);
        }
    }

    go(num_cats - 1);

    printf("%d %d\n", best_sum, best_min);

    return 0;
}
