#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    int id;
    int priority;
    int status;
    char* name;
    char* description;
} todo_item;

// ensure that only unique values are stored in the array, otherwise we would run into double pointer issues.
typedef struct {
    todo_item** todo_list;
    int capacity;
    int size;
} todos;

todo_item* get(int idx, todos* array); 

void set(int idx, todo_item* new_item, todos* array); 

void delete(int idx, todos* array); 

void insert(int idx, todo_item* new_item, todos* array); 

void push_back(todo_item* new_item, todos* array); 

void pop_back(todos* array); 

void push_front(todo_item* new_item, todos* array); 

void pop_front(todos* array); 

todos* initialise_todos(); 

todo_item* create_todo_item(int priority, int status, char* name, char* description); 

todos* filter_todos(int id, int priority, int status, char* name, todos* todo_list); 

void print_todos(todos* todo_list); 

int change_priority(int priority, int id, char* name, todos* todo_list); 

int delete_todo(int id, todos* todo_list); 

int complete_todo(int id, char* name, todos* todo_list); 

void reset_app(todos* old_list, int end_program); 

#endif
