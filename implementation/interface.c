#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <assert.h>

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
    }

    if (check_opt = -1) {
        return 0;
    }
}

int main(int argc, char** argv) {
    todos* todo_database = initialise_todos();
    int failure = handle_options(argc, argv, todo_database);
    if (failure) {
        return 1;
    }
    printf("successful test\n");
    return 0;
}
