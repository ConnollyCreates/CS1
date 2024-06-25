#include <stdio.h>

typedef struct List List;
typedef struct Student Student;

struct Student{
    int grade;
    char * name;
};


struct List{
    int size, cap;
    Student ** arr;
};

Student * createStudent(char * name, int grade) {
    Student * res = (Student *) malloc(sizeof(Student));
    res->name = (char *) malloc(sizeof(char) * strlen(1+ name));
    strcpy(res->name, name);
    res->grade = grade;

}

void append(List * list, char * name, int grade) {
    //Check if array is full
    if(list->cap == list->size) {
       list->cap*=2;
        list->arr = (Student **)realloc(list->arr, sizeof(Student *) * list->cap);
    }

    list->arr[list->size] = createStudent(name, grade);
    list->size++;
}

int main() {


    return 0;
}