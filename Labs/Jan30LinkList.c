#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Inserts 70
#define MAX = 6

typedef struct node node;

struct node{
    node * next;
    int value;
};

node *insertFront(node *, int);
node * removeAll(int ,node *);
void printFwd(node *);

node * removeAll(int value, node * head) {

    node * newHead = head;
    node * prevNode;
    node * temp;

    while(newHead != NULL && newHead->value == value) {

        temp = newHead;
        newHead = newHead->next;
        free(temp);
    }

    prevNode = newHead;
    while(prevNode != NULL && prevNode->next != NULL) {

        if(prevNode->next->value == value) {
            temp = prevNode->next;
            prevNode->next = temp->next;
            free(temp);
        }
        else {
            prevNode = prevNode->next;

        }

    }

    return newHead;
}

int main() {

node * head = NULL;
node * tail = NULL;

/*for(int i = 0; i<Inserts; i++) {

    head=insertFront(head, rand()  % MAX + 1);

}*/

for(int i=0; i<12;i++) {

int value;
scanf("%d",value);
    head = insertFront(head, value);

}

printFwd(head);

for(int i=0; i<10+1; i++) {
    head = removeAll(i, head);
    if(head == NULL) {
        tail = NULL;
    }
}

printFwd(head);

    return 0;
}