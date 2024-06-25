#include <stdio.h>
#include <stdlib.h>

// struct definitions
struct Node
{
    int r, c;
    struct Node *next;
};

struct Stack
{
    struct Node *head;
};

struct Elephant
{
    struct Stack memory;
};

// recommended function prototypes
struct Node *createNode(int row, int col);
void push(struct Stack *stack, int row, int col);
void pop(struct Stack *stack);
void top(struct Stack *stack, int *row_ptr, int *col_ptr);
void addBait(int **grid, int row, int col, int amt);
int eatBait(int **grid, int row, int col);
void move(struct Elephant *elephantPointer, int **grid);
int eat(struct Elephant *elephantPointer, int **grid);
int progress_hour(struct Elephant *ele_arr, int numElephants, int **grid);

// defining the functions
struct Node *createNode(int row, int col)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // uses exit code to quit program if null
        exit(EXIT_FAILURE);
    }
    newNode->r = row;
    newNode->c = col;
    newNode->next = NULL;
    return newNode;
}

// inserts into stack
void push(struct Stack *stack, int row, int col)
{
    struct Node *newNode = createNode(row, col);
    newNode->next = stack->head;
    stack->head = newNode;
}

// deletes something from stack
void pop(struct Stack *stack)
{
    if (stack->head == NULL)
    {
        exit(EXIT_FAILURE);
    }
    struct Node *temp = stack->head;
    stack->head = stack->head->next;
    free(temp);
}

// puts value to top of stack
void top(struct Stack *stack, int *row_ptr, int *col_ptr)
{
    if (stack->head == NULL)
    {
        exit(EXIT_FAILURE);
    }
    *row_ptr = stack->head->r;
    *col_ptr = stack->head->c;
}

// add bait to col and row
void addBait(int **grid, int row, int col, int amt)
{
    grid[row][col] += amt;
}

// elephants eat bait
int eatBait(int **grid, int row, int col)
{
    int eaten = grid[row][col];
    grid[row][col] = 0;
    return eaten;
}

// calculates where elephant moves
void move(struct Elephant *elephantPointer, int **grid)
{
    int row, col;
    top(&(elephantPointer->memory), &row, &col);
    int maxMelons = grid[row][col];
    int newRow = row, newCol = col;

    // Checking close by cells for maximum melons
    if (row > 1 && grid[row - 1][col] > maxMelons)
    {
        maxMelons = grid[row - 1][col];
        newRow = row - 1;
        newCol = col;
    }
    if (row < 500 && grid[row + 1][col] > maxMelons)
    {
        maxMelons = grid[row + 1][col];
        newRow = row + 1;
        newCol = col;
    }
    if (col > 1 && grid[row][col - 1] > maxMelons)
    {
        maxMelons = grid[row][col - 1];
        newRow = row;
        newCol = col - 1;
    }
    if (col < 500 && grid[row][col + 1] > maxMelons)
    {
        maxMelons = grid[row][col + 1];
        newRow = row;
        newCol = col + 1;
    }

    if (newRow != row || newCol != col)
        push(&(elephantPointer->memory), newRow, newCol);
}

int eat(struct Elephant *elephantPointer, int **grid)
{
    int row, col;
    top(&(elephantPointer->memory), &row, &col);
    return eatBait(grid, row, col);
}

int progress_hour(struct Elephant *ele_arr, int numElephants, int **grid)
{
    int totalMelons = 0;
    for (int i = 0; i < numElephants; ++i)
    {
        move(&ele_arr[i], grid);
    }
    for (int i = 0; i < numElephants; ++i)
    {
        totalMelons += eat(&ele_arr[i], grid);
    }
    return totalMelons;
}

int main()
{
    int num;
    scanf("%d", &num);

    struct Elephant *elephants = (struct Elephant *)malloc(num * sizeof(struct Elephant));
    int **grid = (int **)malloc(501 * sizeof(int *));
    if (elephants == NULL || grid == NULL)
    {
        // exits if equal to null
        return 1;
    }

    for (int i = 0; i < 501; ++i)
    {
        grid[i] = (int *)calloc(501, sizeof(int));
        if (grid[i] == NULL)
        {
            return 1;
        }
    }

    for (int i = 0; i < num; ++i)
    {
        int r, c;
        scanf("%d %d", &r, &c);
        push(&(elephants[i].memory), r, c);
    }

    char command[10];
    while (scanf("%s", command) != EOF)
    {
        // Check first characters for command words
        if (command[0] == 'B')
        {
            // bait function
            int r, c, a;
            scanf("%d %d %d", &r, &c, &a);
            addBait(grid, r, c, a);
        }
        else if (command[0] == 'H')
        {
            // hour function
            printf("%d\n", progress_hour(elephants, num, grid));
        }
        else if (command[0] == 'Q')
        {
            // quit function
            break;
        }
    }

    for (int i = 0; i < num; ++i)
    {
        int row, col;
        top(&(elephants[i].memory), &row, &col);
        printf("%d %d\n", row, col);
    }

    // free outstanding memory
    for (int i = 0; i < 501; ++i)
    {
        free(grid[i]);
    }
    free(grid);
    free(elephants);

    return 0;
}
