/*
This program reads in pairs of users representing friends.
Outputs the number of friends each user has and the names of all their friends.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct UserList UserList;
typedef struct User User;
struct User
{
    char **arr;
    int size, cap;
    char *name;
};
struct UserList
{
    int size, cap;
    User *arr;
};
// function to create a list to hold all users and initialize the list
UserList *createUserList()
{
    UserList *ret;
    // allocate memory for 1 list
    ret = (UserList *)malloc(sizeof(UserList));
    ret->size = 0;
    ret->cap = 2;
    // allocate an array to hold all users
    ret->arr = (User *)malloc(sizeof(User) * ret->cap);
    return ret;
}
// Initializing a user
void initializeUser(User *user, char *name)
{
    user->size = 0;
    user->cap = 2;
    // allocate space an array of strings
    user->arr = (char **)malloc(sizeof(char *) * user->cap);
    user->name = strdup(name);
}
// Adding a name to the user list
void append(UserList *list, char *name)
{
    if (list->size == list->cap)
    {
        list->cap *= 2;
        // expand
        list->arr = (User *)realloc(list->arr, sizeof(User) * list->cap);
    }
    initializeUser(&(list->arr[list->size]), name);
    list->size++;
}
// Add friend to a User (Array List append)
void addFriend(User *user, char *friend)
{
    if (user->size == user->cap)
    {
        // Expand
        user->cap *= 2;
        user->arr = (char **)realloc(user->arr, user->cap * sizeof(char *));
    }
    user->arr[user->size] = strdup(friend);
    user->size++;
}
// function goes through the list an find if the names exist
User *findUser(UserList *list, char *name)
{
    // Linear search
    for (int i = 0; i < list->size; i++)
    {
        // Check if the name matches
        if (strcmp(name, list->arr[i].name) == 0)
        {
            return &(list->arr[i]); // Return the user
        }
    }
    // New user
    append(list, name);                  // Create the new user
    return &(list->arr[list->size - 1]); // Return the new user
    // return findUser(list, name); // Do the search again
}
// function takes 2 names and add to each other's friends lists
void addFriendShip(UserList *list, char *a, char *b)
{
    // Find the users
    User *user_a = findUser(list, a);
    User *user_b = findUser(list, b);
    // Add the friend ships
    addFriend(user_a, b);
    addFriend(user_b, a);
}
// print the friends list of a user
void printUser(User *user)
{
    printf("User %s has %d friends who are:\n", user->name, user->size);
    for (int i = 0; i < user->size; i++)
    {
        printf("%s ", user->arr[i]);
    }
    printf("\n\n");
}
// print all users' lists
void printList(UserList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        printUser(&list->arr[i]);
    }
}
// free list of user
void freeList(UserList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        for (int j = 0; j < list->arr->size; j++)
        {
            // free the user's friend list
            free(list->arr[i].arr[j]);
        }
        // free each user's name
        free(list->arr[i].name);
        // free each user
        free(list->arr[i].arr);
    }
    // free the user array
    free(list->arr);
    // free the list of all users
    free(list);
}
int main()
{
    // creating a list of users & allocate memory
    UserList *theList = createUserList();
    char username[100 + 1];
    char user_friend[100 + 1];
    while (1)
    {
        scanf("%s", username);
        if (0 == strcmp("END", username))
            break;
        scanf("%s", user_friend);
        addFriendShip(theList, username, user_friend);
    }
    printList(theList);
    freeList(theList);
    return 0;
}