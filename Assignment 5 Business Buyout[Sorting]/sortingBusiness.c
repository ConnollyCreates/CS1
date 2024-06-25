#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack Stack;

// Stack declaration
struct Stack
{
    long long size;
    int top;
    int *arr;
};

// Stack Prototypes
void initializeStack(Stack *stk, int size);
void push(Stack *stk, int data);
void pop(Stack *stk);
long top(Stack stk);

// Stack functions

void initializeStack(Stack *stk, int size)
{
    stk->size = size; // No values in new stack
    stk->top = -1;    // Empty stack
    stk->arr = (int *)malloc(sizeof(int) * stk->size);
}

void push(Stack *stk, int data)
{

    stk->arr[++stk->top] = data;
    stk->size++;
}
void pop(Stack *stk)
{

    stk->size--;
    stk->top--;
}

// Merge sort function
void merge_sort(long long *arr, long long len)
{
    // Base Case
    if (len <= 1)
    {
        return;
    }
    // Sort the 2 halves
    merge_sort(arr, len / 2);
    merge_sort(arr + (len / 2), len - (len / 2));
    // Merge the 2 halves into a temp array
    long long *tmp = (long long *)malloc(sizeof(long long) * len);
    int fptr = 0;
    int bptr = len / 2;
    for (int i = 0; i < len; i++)
    {
        if (fptr == len / 2 || (bptr != len && arr[bptr] < arr[fptr]))
        {
            tmp[i] = arr[bptr];
            bptr++;
        }
        else
        {
            tmp[i] = arr[fptr];
            fptr++;
        }
    }
    // Move the contents into the original array
    for (int i = 0; i < len; i++)
    {
        arr[i] = tmp[i];
    }
    // Clean up the temp array
    free(tmp);
}

int shopBuyout(long long shop_wealths[], int numShop, long long btsWealth, Stack *stack1, Stack *stack2)
{
    int purchasedShops = 0;
    int progress = 0;

    //While our wealth is less than the most expensive store and while stack isnt empty
    while (btsWealth < stack2->arr[0] && stack1->top != 0)
    {
        //Buys the most expensive shop we can afford and adds wealth to ours
        if (btsWealth > stack1->arr[stack1->top])
        {
            progress = purchasedShops;
            btsWealth += stack1->arr[stack1->top];
            purchasedShops++;
        }
        //Pops the shop we just bought
        pop(stack1);

        //if we can now afford a shop we could not have afforded previously
        if (btsWealth > stack2->arr[stack2->top])
        {
            btsWealth += stack2->arr[stack2->top];
            purchasedShops++;
            pop(stack2);
        }

        //When we no longer are able to purchase shops
        if (progress == purchasedShops)
        {
            break;
        }
    }

    //Return -1 if impossible to be most wealthy
    if (btsWealth < stack2->arr[0])
    {
        return -1;
    }

    return purchasedShops;
}

int main()
{

    Stack s1;
    Stack s2;

    long numShops, btsWealth;

    //Scan number of shops and starting wealth
    scanf("%ld %ld", &numShops, &btsWealth);

    initializeStack(&s1, numShops);
    initializeStack(&s2, numShops);

    //Allocate memory for all the shops
    long long *shop_wealths = (long long *)malloc(numShops * sizeof(long long));

    // Null check if shop wealths equal null
    if (shop_wealths == NULL)
    {
        return 1;
    }

    //Get the shop's wealth
    for (int i = 0; i < numShops; i++)
    {
        scanf("%lld", &shop_wealths[i]);
    }

    //Sorts the shops
    merge_sort(shop_wealths, numShops);

    // Checking wealthiest shops to least valueable shops
    for (int i = 0; i < numShops; i++)
    {
        // Puts shop in stack if affordable

        if (btsWealth > shop_wealths[i])
        {
            push(&s1, shop_wealths[i]);
        }
    }

    // Puts shop in a cant afford stack
    for (int i = numShops - 1; i > 0; i--)
    {
        if (btsWealth <= shop_wealths[i])
        {
            push(&s2, shop_wealths[i]);
        }
    }

    //Buying out the shops
    int minShops = shopBuyout(shop_wealths, numShops, btsWealth, &s1, &s2);

    //Printing the result
    printf("%d\n", minShops);

    free(shop_wealths);
    free(s1.arr);
    free(s2.arr);

    return 0;
}