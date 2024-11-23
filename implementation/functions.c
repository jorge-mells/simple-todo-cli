#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    int priority;
    int status;
    char* name;
    char* description;
} todo_item;

typedef struct {
    todo_item** todolist;
} todos;

todos* initialise_todos() {
    todos* newtodolist = (todos*) calloc(1, sizeof(todos));
    todos -> todolist = (todo_item**) calloc(10, sizeof(todo_item*));
    return todos*;
}
