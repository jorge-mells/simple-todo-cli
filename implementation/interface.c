#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"

static struct option long_options[] = {
    {"name", required_argument, NULL, 1}, 
    {"description", required_argument, NULL, 2}, 
    {"priority", required_argument, NULL, 3}, 
    {"list", no_argument, NULL, 4},
    {"complete", no_argument, NULL, 5},
    {"pending", no_argument, NULL, 6},
    {"id", required_argument, NULL, 7},
    {"help", no_argument, NULL, 8},
    {"delete", no_argument, NULL, 9},
    {"reset", no_argument, NULL, 10},
    {0, 0, 0, 0}
};

int handle_todo_creation(int argc, char** argv, todos* todo_array) {
    char* name = optarg;
    int check_opt = getopt_long(argc, argv, "", long_options, NULL);
    char* description; 
    if (check_opt == 2) {
        description = optarg;
    } else {
        printf("you should provide a description as your second argument\n");
        return 1;
    }
    check_opt = getopt_long(argc, argv, "", long_options, NULL);
    int priority;
    if (check_opt == 3) {
        priority = atoi(optarg);
    } else {
        priority = 0;
    }
    todo_item* new_todo = create_todo_item(priority, -1, name, description);
    push_back(new_todo, todo_array);
    return 0;
}

int handle_printing(int argc, char** argv, todos* todo_array) {
    int check_opt;
    check_opt = getopt_long(argc, argv, "", long_options, NULL);
    int priority; 
    if (check_opt == 3) {
        priority = atoi(optarg);
        todos* filtered = filter_todos(-1, priority, 0, NULL, todo_array);
        print_todos(filtered);
        free(filtered);
    } else if (check_opt == 5) {
        todos* filtered = filter_todos(-1, -1, 1, NULL, todo_array);
        print_todos(filtered);
        free(filtered);
    } else if (check_opt == 6) {
        todos* filtered = filter_todos(-1, -1, -1, NULL, todo_array);
        print_todos(filtered);
        free(filtered);
    } else {
        print_todos(todo_array);
    }
    return 0;
}

int handle_todo_completion(int argc, char** argv, todos* todo_array) {
    int check_opt;
    check_opt = getopt_long(argc, argv, "", long_options, NULL);
    if (check_opt == 1) {
        char* name = optarg;
        todos* filtered = filter_todos(-1, -1, 0, name, todo_array);
        if (filtered -> capacity == 1) {
            (filtered -> todo_list)[0] -> status = 1;
        } else {
            printf("this name is not unique or cannot be found, please use an id\n");
            return 1;
        }
        free(filtered);
    } else if (check_opt == 7) {
        int id = atoi(optarg);
        todos* filtered = filter_todos(id, -1, 0, NULL, todo_array);
        assert(filtered -> capacity == 1 || filtered -> capacity == 0);
        if (filtered -> capacity == 1) {
            (filtered -> todo_list)[0] -> status = 1;
        }
        free(filtered);
    }
    return 0;
}

void handle_help() {
    char* help = "(note that all options in square brackets are not compulsory.)\nto create a new todo, use:\n\t --name 'name' --description 'description' [priority='priority'] (priority must be between 1 and 3)\nto print your todos, use\n\t --list [--complete] [--pending] [--priority='priority'] (in this case priority can also be 0)\nto complete todos, use\n\t --complete --id | --name (followed by the appropriate argument)\nto display this page use\n\t --help\nyou can delete with\n\t --delete --id | --name (followed by appropriate argument)\nyou can reset with \n\t --reset\n(please don't do anything 'stupid', this app is very fragile)\n";
    printf("%s\n", help);
}

int handle_todo_priority(int argc, char** argv, todos* todo_array) {
    int check_opt;
    int priority = atoi(optarg);
    check_opt = getopt_long(argc, argv, "", long_options, NULL);
    if (check_opt == 1) {
        char* name = optarg;
        todos* filtered = filter_todos(-1, -1, 0, name, todo_array);
        if (filtered -> capacity == 1) {
            (filtered -> todo_list)[0] -> priority = priority;
        } else {
            printf("this name is not unique or cannot be found, please use an id\n");
            return 1;
        }
        free(filtered);
    } else if (check_opt == 7) {
        int id = atoi(optarg);
        todos* filtered = filter_todos(id, -1, 0, NULL, todo_array);
        assert(filtered -> capacity == 1 || filtered -> capacity == 0);
        if (filtered -> capacity == 1) {
            (filtered -> todo_list)[0] -> priority = priority;
        }
        free(filtered);
    }
    return 0;
}


int handle_delete(int argc, char** argv, todos* todo_array) {
    int check_opt;
    check_opt = getopt_long(argc, argv, "", long_options, NULL);
    if (check_opt == 1) {
        char* name = optarg;
        todos* filtered = filter_todos(-1, -1, 0, name, todo_array);
        if (filtered -> capacity == 1) {
            int id = (filtered -> todo_list)[0] -> id;
            delete(id, todo_array);
        } else {
            printf("this name is not unique or cannot be found, please use an id\n");
            return 1;
        }
        free(filtered);
    } else if (check_opt == 7) {
        int id = atoi(optarg);
        todos* filtered = filter_todos(id, -1, 0, NULL, todo_array);
        assert(filtered -> capacity == 1 || filtered -> capacity == 0);
        if (filtered -> capacity == 1) {
            id = (filtered -> todo_list)[0] -> id;
        }
        free(filtered);
        delete(id, todo_array);
    }
    return 0;
}

int handle_options(int argc, char** argv, todos* todo_array) {
    int selected_option = -1;
    int check_opt = getopt_long(argc, argv, "", long_options, NULL);
    // handle the creation of new todos
    if (check_opt == 1) {
        int success = handle_todo_creation(argc, argv, todo_array);
        return success;
    }

    if (check_opt == 4) {
        int success = handle_printing(argc, argv, todo_array);
        return success;
    }

    if (check_opt == 5) {
        int success = handle_todo_completion(argc, argv, todo_array);
        return success;
    }

    if (check_opt == 8) {
        handle_help();
        return 0;
    }

    if (check_opt == 9) {
        int success = handle_delete(argc, argv, todo_array);
        return success;
    }

    if (check_opt == 10) {
        return 2;
    }

    if (check_opt == -1) {
        return 0;
    }

    if (check_opt == '?') {
        printf("\nyou probably passed the incorrect option. Here is some help\n\n");
        handle_help();
        return 0;
    }
}

todos* retrieve_data() {
    char *home = getenv("HOME");
    if (home == NULL) {
        /* handle the error, although POSIX requires HOME to be set */
    }
    chdir(home);
    todos* todo_database = initialise_todos();
    FILE* fptr = fopen(".todo_data", "r");
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
        push_back(new_todo_item, todo_database);
    }
    fclose(fptr);
    return todo_database;
}

int store_data(todos* todo_database) {
    char *home = getenv("HOME");
    if (home == NULL) {
        /* handle the error, although POSIX requires HOME to be set */
    }
    chdir(home);
    FILE* fptr = fopen(".todo_data", "w");
    if (!fptr) {
        return 1;
    }
    
    for (int i = 0; i < todo_database -> capacity; i++) {
        todo_item* item = get(i, todo_database);
        if (item != NULL) {
            fprintf(fptr, "%d,%d,%d,%s,%s\n", item -> id, item -> priority, item -> status, item -> name, item -> description);
        }
    }

    fclose(fptr);
    return 0;
}

int main(int argc, char** argv) {
    todos* todo_database = retrieve_data();
    int failure = handle_options(argc, argv, todo_database);
    if (failure == 1) {
        printf("option handling problems\n");
        return 1;
    }
    if (failure == 2) {
        todo_database = initialise_todos();
    }
    failure = store_data(todo_database);
    if (failure) {
        printf("storage problem\n");
        return 1;
    }
    reset_app(todo_database, 1);
    if (optind == 1) {
        printf("\nyou probably passed the incorrect option. Here is some help\n\n");
        handle_help();
        return 0;
    }
    return 0;
}
