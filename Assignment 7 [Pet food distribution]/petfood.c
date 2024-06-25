#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP 32

//Recommended struct
typedef struct Node {
    int myAmount;
    int subTrieAmount;
    struct Node* children[MAP];
} Node;

//Creating a node in the trie
Node* newNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->myAmount = 0;
    node->subTrieAmount = 0;
    return node;
}

//Mapping characters to number values
int charToIndex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'v') return 10 + (c - 'a');
    return -1; //return if invalid
}

//Inserts into the trie
void change(Node* root, char* response, int amount) {
    Node* current = root;
    for (int i = 0; response[i]; i++) {
        int index = charToIndex(response[i]);
        if (!current->children[index]) {
            current->children[index] = newNode();
        }
        current = current->children[index];
        current->subTrieAmount += amount;
    }
    current->myAmount += amount;
}

//Function to get current sum of families
void sum(Node* root, char* prefix, int* min, int* max) {
    Node* current = root;
    *min = 0;
    *max = 0;
    //Checks to see if the prefix matches the users input
    for (int i = 0; prefix[i]; i++) {
        int index = charToIndex(prefix[i]);
        if (!current->children[index]) {
            return; //return if no prefix is found
        }
        current = current->children[index];
    }
    *min = current->subTrieAmount; 
    *max = current->subTrieAmount;
    if (prefix[strlen(prefix) - 1] == '\0') {
        *max += current->myAmount; 
    }
}

//Free all memory from the trie
void freeTrie(Node* node) {
    //base case
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < MAP; i++) {
        freeTrie(node->children[i]);
    }
    free(node);
}

int main() {
    //variable declarations
    Node* root = newNode();
    char cmd[10];
    char ans[10000 + 1];
    char newAns[10000 + 1];
    int amt;

    //loop of program
    while (scanf("%s", cmd) != EOF) {
        if (strcmp(cmd, "ADD") == 0) {
            scanf("%s %d", ans, &amt);
            change(root, ans, amt);
        } else if (strcmp(cmd, "CHANGE") == 0) {
            scanf("%s %s", ans, newAns);
            int currentAmount;
            //get cur sum
            sum(root, ans, &currentAmount, &currentAmount);
            //Negates the current value of food from the trie
            change(root, ans, -currentAmount);
            //Inserts new food value into the trie
            change(root, newAns, currentAmount);
        } else if (strcmp(cmd, "SUM") == 0) {
            scanf("%s", ans);
            int min, max;
            sum(root, ans, &min, &max);
            printf("%d %d\n", min, max);
        } else if (strcmp(cmd, "QUIT") == 0) {
            break;
        }
    }

    //Free memory
    freeTrie(root);
    return 0;
}
