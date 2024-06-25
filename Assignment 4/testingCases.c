#include <stdio.h>

#define MAX_CATS 15
#define MAX_FAMILIES 3
#define MAX_COZINESS 1000
#define MIN_COZINESS -1000

int num_cats;
int max_coziness_sum = MIN_COZINESS * MAX_CATS;
int min_coziness = MAX_COZINESS;

void assign_cats(int current_cat, int current_assignment[MAX_CATS], int coziness_levels[MAX_CATS][MAX_FAMILIES], int interactions[MAX_CATS][MAX_CATS], int total_coziness[MAX_CATS]) {
    if (current_cat == num_cats) {
        int sum = 0;
        for (int i = 0; i < num_cats; i++) {
            sum += total_coziness[i];
        }
        if (sum > max_coziness_sum) {
            max_coziness_sum = sum;
        }
        int min_cat_coziness = total_coziness[0];
        for (int i = 1; i < num_cats; i++) {
            if (total_coziness[i] < min_cat_coziness) {
                min_cat_coziness = total_coziness[i];
            }
        }
        if (min_cat_coziness > min_coziness) {
            min_coziness = min_cat_coziness;
        }
        return;
    }

    for (int house = 0; house < MAX_FAMILIES; house++) {
        current_assignment[current_cat] = house;
        total_coziness[current_cat] = coziness_levels[current_cat][house];
        
        for (int other_cat = 0; other_cat < current_cat; other_cat++) {
            if (current_assignment[other_cat] == house) {
                total_coziness[current_cat] += interactions[current_cat][other_cat];
            }
        }

        assign_cats(current_cat + 1, current_assignment, coziness_levels, interactions, total_coziness);

        // Backtrack: Reset values for next iteration
        total_coziness[current_cat] = 0;
    }
}

int main() {
    int coziness_levels[MAX_CATS][MAX_FAMILIES];
    int interactions[MAX_CATS][MAX_CATS];

    scanf("%d", &num_cats);

    for (int i = 0; i < num_cats; i++) {
        for (int j = 0; j < MAX_FAMILIES; j++) {
            scanf("%d", &coziness_levels[i][j]);
        }
    }

    for (int i = 0; i < num_cats; i++) {
        for (int j = 0; j < num_cats; j++) {
            scanf("%d", &interactions[i][j]);
        }
    }

    int current_assignment[MAX_CATS] = {0};
    int total_coziness[MAX_CATS] = {0};

    assign_cats(0, current_assignment, coziness_levels, interactions, total_coziness);

    printf("%d %d\n", max_coziness_sum, min_coziness);

    return 0;
}
