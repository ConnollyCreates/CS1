
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CMD_LEN 4
#define DIR_COUNT 4
#define ROW_COUNT 502
#define COL_COUNT 502

int dx[DIR_COUNT] = {1, 0, -1, 0};
int dy[DIR_COUNT] = {0, 1, 0, -1};

typedef struct Elephant Elephant;
typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
   int r, c;
   Node * next;
};

struct Stack {
   Node * head;
   int size;
};

struct Elephant {
   Stack memory;
};

Node * createNode(int r, int c) {
   Node * res = (Node *) malloc(sizeof(Node));
   res->r = r;
   res->c = c;
   res->next = NULL;
   return res;
}

void push(Stack * stk, int r, int c) {
   Node * newHead = createNode(r, c);
   newHead->next = stk->head;
   stk->head = newHead;
   stk->size++;
}

void pop(Stack * stk) {
   stk->size--;
   Node * tmp = stk->head;
   stk->head = stk->head->next;
   free(tmp);
}

void top(Stack * stk, int * r, int * c) {
   *r = stk->head->r;
   *c = stk->head->c;
}

Elephant * readElephants(int * num) {
   scanf("%d", num);
   Elephant * ele_arr = (Elephant *) malloc(sizeof(Elephant) * (*num));
   for (int i = 0; i < *num; i++) {
      int r, c;
      scanf("%d%d", &r, &c);
      ele_arr[i].memory.size = 0;
      ele_arr[i].memory.head = NULL;
      push(&(ele_arr[i].memory), r, c);
   }
   return ele_arr;
}

void move(Elephant * ele, int ** grid) {
   int row;
   int col;
   
   // Get the location of the elephant
   top(&(ele->memory), &row, &col);

   // Do we have something to eat???
   if (grid[row][col]) {
      return;
   }

   // Try looking adjacent
   int bestAmt = 0;
   int bestRow = 0;
   int bestCol = 0;
   int bad = 0;
   for (int i = 0; i < DIR_COUNT; i++) {
      int newRow = row + dx[i];
      int newCol = col + dy[i];

      // Better melons
      if (grid[newRow][newCol] > bestAmt) {
         bad = 0;
         bestAmt = grid[newRow][newCol];
         bestRow = newRow;
         bestCol = newCol;
      } else if (grid[newRow][newCol] && grid[newRow][newCol] == bestAmt) {
         // A tie :(
         bad = 1;
      }
   }

   // Sanity check
   assert(!bad);

   // Move if can eat
   if (bestAmt) {
      push(&(ele->memory), bestRow, bestCol);
      return;
   }

   // Check if we should move back
   if (ele->memory.size > 1) {
      pop(&(ele->memory));
   }
}

int eat(Elephant * ele, int ** grid) {
   int row;
   int col;
   int res;
   
   top(&(ele->memory), &row, &col);
   res = grid[row][col];
   grid[row][col] = 0;

   return res; 
}

int hour(Elephant * arr, int len, int ** grid) {
   int res = 0;
   for (int i = 0; i < len; i++) {
      move(arr + i, grid);
   }
   for (int i = 0; i < len; i++) {
      res += eat(arr + i, grid);
   }
   return res;
}

int main() {
   Elephant * ele_arr;
   int done;
   int ele_num;
   char cmd[CMD_LEN + 1];
   int ** grid;
   int row;
   int col;
   int amt;

   // Create the grid
   grid = (int **) malloc(sizeof(int *) * ROW_COUNT);
   for (int i = 0; i < ROW_COUNT; i++) {
      grid[i] = (int *) calloc(COL_COUNT, sizeof(int));
   }

   // Read the elephant array
   ele_arr = readElephants(&ele_num);
   
   // Handle multiple commands
   done = 0;
   while (!done) {
      scanf("%s", cmd);
      if (!strcmp(cmd, "QUIT")) {
         done = 1;
      } else if (!strcmp(cmd, "HOUR")) {
         printf("%d\n", hour(ele_arr, ele_num, grid));
      } else if (!strcmp(cmd, "BAIT")) {
         scanf("%d%d%d", &row, &col, &amt);
         grid[row][col] += amt;
      }
   }

   // Print the resulting location of the elephants
   for (int i = 0; i < ele_num; i++) {
      top(&(ele_arr[i].memory), &row, &col);
      printf("%d %d\n", row, col);
   }

   return 0;
}

