void push(Stack *stk, int data)
{
    if (stk->top < stk->size - 1)
    {
        stk->arr[++stk->top] = data; // Increment before using as index
        // stk->size++; // Remove this if size represents max capacity
    }
    else
    {
        printf("Stack is full!\n");
    }
}

void pop(Stack *stk) 
{
if (stk->top > -1) {
    stk->top--;
    // stk->size--; // Remove this if size represents current number
} else {
    printf("Stack is empty!\n");
}


}



void print(long long *arr, long long len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

long long peek(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack is empty!\n");
        return -1; // Return an invalid value to indicate an empty stack
    }
    return stack->arr[stack->top];
}