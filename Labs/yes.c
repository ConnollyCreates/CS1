#include <stdio.h>
#include <string.h>

void removeForbiddenChars(char *str, char *forbiddenChars) {
    int len = strlen(str);
    int forbiddenLen = strlen(forbiddenChars);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < forbiddenLen; j++) {
            if (str[i] == forbiddenChars[j]) {
                // Remove the forbidden character by shifting remaining characters
                memmove(&str[i], &str[i + 1], len - i);
                len--;
                i--; // Re-check the same index after shifting
                break;
            }
        }
    }
}

int main() {
    char originalString[4000]; // Maximum length is 100 characters
    char forbiddenChars[21];  // Maximum length is 20 characters
    int n;

    // Input the original string
    scanf("%s", originalString);

    // Input the number of characters to consider for removal
    scanf("%d", &n);

    // Input the forbidden characters
    for (int i = 0; i < n; i++) {
        scanf(" %c", &forbiddenChars[i]);
    }

    // Ensure the forbiddenChars string is null-terminated
    forbiddenChars[n] = '\0';

    // Remove forbidden characters
    removeForbiddenChars(originalString, forbiddenChars);

    // Output the modified string
    printf("%s\n", originalString);

    return 0;
}
