#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>

#include "functions.h"

void handle_new_todo(int priority, int status, char* name, char* description, todos* todo_array) {
    todo_item* new_todo = create_todo_item(priority, status, name, description);
    push_back(new_todo, todo_array);
}

int handle_options(int argc, char** argv, todos* todo_array) {
    int selected_option = -1;
    static struct option long_options[] = {
        {"new", required_argument, NULL, 1}, 
        {"name", required_argument, NULL, 2}, 
        {"priority", required_argument, NULL, 3}, 
        {"list", no_argument, NULL, 4},
        {0, 0, 0, 0}
    };
    int check_opt = getopt_long(argc, argv, "", long_options, &selected_option);
    // handle the creation of new todos
    if (check_opt == 1) {
        char* description = optarg;
        check_opt = getopt_long(argc, argv, "", long_options, &selected_option);
        char* name; 
        if (check_opt == 2) {
            name = optarg;
        } else {
            printf("you should provide a name as your second argument\n");
            return 1;
        }
        check_opt = getopt_long(argc, argv, "", long_options, &selected_option);
        int priority;
        if (check_opt == 3) {
            priority = atoi(optarg);
        } else {
            priority = 0;
        }
        handle_new_todo(priority, -1, name, description, todo_array);
        return 0;
    }

    if (check_opt == 4) {
        print_todos(todo_array);
        return 0;
    }

    if (check_opt == -1) {
        return 0;
    }
}

todos* retrieve_data() {
    todos* todo_database = initialise_todos();
    FILE* fptr = fopen("data", "r");
    if (!fptr) {
        return todo_database;
    }

    while (1) {
        int id, priority, status;
        char name[100], description[1000];
        memset(name, 0, 100);
        memset(description, 0, 1000);
        int eof = fscanf(fptr, "%d,%d,%d,", &id, &priority, &status);
        if (eof == -1) {
            break;
        }
        int i = 0;
        char char_read;
        while (char_read != ',') {
            fscanf(fptr, "%c", &char_read);
            name[i] = char_read;
            i++;
        }
        name[--i] = '\0';
        char* actual_name = (char*) calloc(i, sizeof(char));
        strcpy(actual_name, name);
        i = 0;
        char_read = '\0';
        while (char_read != '\n') {
            fscanf(fptr, "%c", &char_read);
            description[i] = char_read;
            i++;
        }
        description[--i] = '\0';
        char* actual_description = (char*) calloc(i, sizeof(char));
        strcpy(actual_description, description);

        todo_item* new_todo_item = create_todo_item(priority, status, actual_name, actual_description);
        assert(new_todo_item -> id == id); 
        push_back(new_todo_item, todo_database);
    }
    fclose(fptr);
    return todo_database;
}

int store_data(todos* todo_database) {
    FILE* fptr = fopen("data", "w");
    if (!fptr) {
        return 1;
    }
    
    for (int i = 0; i < todo_database -> capacity; i++) {
        todo_item* item = get(i, todo_database);
        fprintf(fptr, "%d,%d,%d,%s,%s\n", item -> id, item -> priority, item -> status, item -> name, item -> description);
    }

    fclose(fptr);
    return 0;
}

int main(int argc, char** argv) {
    todos* todo_database = retrieve_data();
    int failure = handle_options(argc, argv, todo_database);
    if (failure) {
        printf("option handling problems");
        return 1;
    }
    failure = store_data(todo_database);
    if (failure) {
        printf("storage problem\n");
        return 1;
    }
    reset_app(todo_database, 1);
    printf("successful test\n");
    return 0;
}
