#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "functions.h"

static int id = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

void reallocate(todos* array) {
    if (array -> capacity == array -> size) {
        array -> size = 2 * array -> size;
        todo_item** new_array = (todo_item**) calloc(array -> size, sizeof(todo_item*));
        for (int i = 0; i < array -> size; i++) {
            new_array[i] = (array -> todo_list)[i];
        }
        free(array -> todo_list);
        array -> todo_list = new_array;
    } else if (array -> capacity == array -> size / 4) {
        array -> size = 2 * (array -> capacity + 1);
        todo_item** new_array = (todo_item**) calloc(array -> size, sizeof(todo_item*));
        for (int i = 0; i < array -> size; i++) {
            new_array[i] = (array -> todo_list)[i];
        }
        free(array -> todo_list);
        array -> todo_list = new_array;
    }
}

todo_item* get(int idx, todos* array) {
    assert(idx >= 0 && idx < array -> size);
    if (array -> capacity > idx) {
        return (array -> todo_list)[idx];
    }
    return NULL;
}

void set(int idx, todo_item* new_item, todos* array) {
    // ensure that the index passed to set is small enough
    assert(idx >= 0 && idx < array -> size);
    (array -> todo_list)[idx] = new_item;
    array -> capacity = max(array -> capacity, idx + 1);
    reallocate(array);
}

void delete(int idx, todos* array) {
    // ensure that the index is not negative and small enough
    assert(idx >= 0 && idx < array -> size);
    todo_item* remove = (array -> todo_list)[idx];
    (array -> todo_list)[idx] = NULL;
    free(remove);
    array -> capacity = max(array -> capacity, idx - 1);
    reallocate(array);
}

void insert(int idx, todo_item* new_item, todos* array) {
    // ensure that the index is not negative and small enough
    assert(idx >= 0 && idx < array -> size);
    for (int i = array -> capacity; i >= idx; i--) {
        (array -> todo_list)[i] = (array -> todo_list)[i - 1];
    }
    (array -> todo_list)[idx] = new_item;
    (array -> capacity)++;
    reallocate(array);
}

void push_back(todo_item* new_item, todos* array) {
   (array -> todo_list)[array -> capacity] = new_item;
   (array -> capacity)++;
   reallocate(array);
}

void pop_back(todos* array) {
    todo_item* remove = (array -> todo_list)[array -> capacity - 1];
    (array -> todo_list)[array -> capacity - 1] = NULL;
    free(remove);
    (array -> capacity) = max(array -> capacity - 1, 0);
    reallocate(array);
}

void push_front(todo_item* new_item, todos* array) {
    insert(0, new_item, array);
}

void pop_front(todos* array) {
    free((array -> todo_list)[0]);
    (array -> todo_list)[0] = NULL;
    for (int i = 1; i < array -> capacity; i++) {
        (array -> todo_list)[i - 1] = (array -> todo_list)[i];
    }
    array -> capacity = max(array -> capacity - 1, 0);
}

todos* initialise_todos() {
    todos* new_todo_list = (todos*) calloc(1, sizeof(todos));
    new_todo_list -> todo_list = (todo_item**) calloc(1, sizeof(todo_item*));
    new_todo_list -> capacity = 0;
    new_todo_list -> size = 1;
    return new_todo_list;
}

todo_item* create_todo_item(int priority, int status, char* name, char* description) {
    todo_item* new_todo_item = (todo_item*) calloc(1, sizeof(todo_item));
    new_todo_item -> id = id++;
    new_todo_item -> priority = priority;
    new_todo_item -> status = status;
    new_todo_item -> name = name;
    new_todo_item -> description = description;
    return new_todo_item;
}

todos* filter_todos(int id, int priority, int status, char* name, todos* todo_list) {
    todos* temporary_todos = initialise_todos();
    if (id >= 0) {
        assert(priority == 0 && status == 0 && name == NULL);
    } else {
        assert((priority == 0 && status == 0) || (priority == 0 && name == NULL) || (status == 0 && name == NULL));
    }
    if (id >=0) {
        for (int i = 0; i < todo_list -> capacity; i++) {
            if ((todo_list -> todo_list)[i] -> id == id) {
                push_back((todo_list -> todo_list)[i], temporary_todos);
            }
        }
        return temporary_todos;
    }

    if (priority != 0) {
        assert(priority > 0 && priority < 4);
        for (int i = 0; i < todo_list -> capacity; i++) {
            if ((todo_list -> todo_list)[i] -> priority == priority) {
                push_back((todo_list -> todo_list)[i], temporary_todos);
            }
        }
        return temporary_todos;
    }

    if (status != 0) {
        assert(status == 1 || status == -1);
        for (int i = 0; i < todo_list -> capacity; i++) {
            if ((todo_list -> todo_list)[i] -> status == status) {
                push_back((todo_list -> todo_list)[i], temporary_todos);
            }
        }
        return temporary_todos;
    }

    if (name != NULL) {
        for (int i = 0; i < todo_list -> capacity; i++) {
            if (strcmp((todo_list -> todo_list)[i] -> name, name) == 0) {
                push_back((todo_list -> todo_list)[i], temporary_todos);
            }
        }
        return temporary_todos;
    }
}

void print_todos(todos* todo_list) {
    printf("id priority status name description\n");
    for (int i = 0; i < todo_list -> capacity; i++) {
        todo_item* item = (todo_list -> todo_list)[i];
        printf("%d  %d  %d  %s  %s\n", item -> id, item -> priority, item -> status, item -> name, item -> description);
    }
}


int change_priority(int priority, int id, char* name, todos* todo_list) {
    todos* filtered = filter_todos(-1, 0, id, name, todo_list);
    if (filtered -> capacity != 1) {
        return 1;
    }
    (filtered -> todo_list)[0] -> priority = priority;
    free(filtered);
    return 0;
}

int delete_todo(int id, todos* todo_list) {
    for (int i = 0; i < todo_list -> capacity; i++) {
        if ((todo_list -> todo_list)[i] -> id == id) {
            delete(i, todo_list);
            return 0;
        }
    }
    return 1;
}

int complete_todo(int id, char* name, todos* todo_list) {
    todos* filtered = filter_todos(-1, 0, id, name, todo_list);
    if (filtered -> capacity != 1) {
        return 1;
    }
    (filtered -> todo_list)[0] -> status = 1; 
    free(filtered);
    return 0;
}

todos* reset_app(todos* old_list, int end_program) {
    for (int i = 0; i < old_list -> capacity; i++) {
        free((old_list -> todo_list)[i]);
    }
    free(old_list);
    if (end_program) {
        return NULL;
    } else {
        return initialise_todos();
    }
}
