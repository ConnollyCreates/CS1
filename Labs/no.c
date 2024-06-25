#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestCommonSequence(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Create a 2D array to store lengths of common suffixes
    int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    int result = 0;

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                result = max(result, dp[i][j]);
            } else
                dp[i][j] = 0;
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    char str1[20002];
    char str2[20002];

    // Input the first DNA sequence
    scanf("%s", str1);

    // Input the second DNA sequence
    scanf("%s", str2);

    // Find the length of the longest contiguous sequence
    int length = longestCommonSequence(str1, str2);

    // Output the result
    printf("%d\n", length);

    return 0;
}
