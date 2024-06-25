#include <stdio.h>
#include <stdlib.h>

typedef struct author_t author_t;
typedef struct book_t book_t;

struct author_t
{
    char name[20];
    int birthYear;
    int publishings;

};

struct book_t {
    char name[20];
    int year;
    int numAuthors;
    author_t * authors;

};

book_t * readLib(int * num_book_ptr) {
    scanf("%d", num_book_ptr);
    book_t * res = (book_t *)malloc((*num_book_ptr) * sizeof(book_t));
    for(int i = 0; i< (*num_book_ptr);i++) 
    {
        scanf("%s%d%d",res[i].name, &res[i].year, &res[i].numAuthors);
        res[i].authors = (author_t *)malloc(res[i].numAuthors * sizeof(author_t));
        for(int j = 0; j < res[i].authors; j++) {
            author_t * a = &(res[i].authors[j]);
            scanf("%s%d%d", a->name, &(a->birthYear), &(a->publishings));
        }
    }
}

void freeAll(book_t * books, int num_books) {
    for(int i = 0; i<num_books; i++) {
        free(books[i].authors);
    }
    free(books);
}

void printAuthor(author_t author) {
    printf("  %s\n", author.name);
}

void printBook(book_t book) {
    printf("The book is named%s" , book.name);
    printf("The author is%s" , book.name);
    for(int i = 0; i< book.numAuthors; i++) {
        printAuthor(book.authors[i]);
    }
}

void printLib(book_t * arr, int numBooks) {
    for(int i = 0; i< numBooks; i++) {
        printBook(arr[i]);
    }
}

int main() 
{

int num_books;
book_t * arr = readLib(&num_books);
printLib(arr, num_books);
    return 0;
}