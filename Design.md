# About

This is a basic todo app written in C. 

# Specification

This todo app can create new todos, display todos, display basic help info,
remove todos, and change the priorities of todos.

- Creating Todos
A simple todo can be created by using the --description flag and passing a string describing the todo.
A --name flag has to be passed as well to identify the todo.
The todo might be assigned a priority as well, using the --priority='priority' flag. There are
three possible priority levels assigned the values 1, 2 and 3 with 1 being the lowest priority.

- Displaying Todos
All todos may be listed by passing the --list flag to the program. Todos of a particular priority may be listed by passing the --priority='priority' flag. Completed todos may also be listed using the --complete flag. All todos are listed via the following pattern. 'id priority name status description' There are 2 possible statuses a todo might have. It might either be pending or completed. Pending todos may be listed with the --pending flag. To complete a todo, use either the --name or --id flag to identify the todo and pass the --complete flag.

- Displaying basic help info
To display help info for all possible flags , the --help flag may be passed. Unfortunately, this is the only flag available to display help info for any unfamiliar users.

- Changing the priority of todos
The priority of a todo may be changed using the --priority='priority' flag. Any value between 1 and 3 is accepted to be used to change the priority. All other values are rejected. The todo to be accessed may be identified by id with the --id flag or by name with the --name flag.

Finally it would always be possible to reset the program by passing the --reset flag.

The first flags allowed are the following: --description, --list --help, --reset, --delete, --complete, --priority='priority'. Other flags may follow after these flags.
Only one of these flags may be first, and these flags cannot be used together.

# Implementation

There are two C files. One with functions to handle the various features, and another to provide the interface. Each todo item will be a struct which describes the description, the priority and the status. All todo items are stored in a dynamic array. The functions to handle features are:

1. todo_item* create_todo_item(int id, int priority, int status, char* name, char* description) (the name and description must be a null terminated string.
2. todo_item** initialise_todos()
3. todo_item** filter_todos(todo_item** todos, int priority, int status, char* name)
4. void print_todos(todo_item** todos)
5. void print_help()
6. char* change_priority(int priority, int id, char* name, todo_item** todos)
7. char* delete_todo(int id, todo_item** todos)
8. char* complete_todo(todo_item** todos, int id, char* name);
9. int* reset_app(todo_item** todos);

The remaining functions handle the interface:
1. handle_options(parameters would be specified later)
2. main(int argc, char** argv)

Finally there are also functions to handle the deletion of the todo array.

!! IMPORTANT !!
Don't forget to add scripts to install and uninstall the program, so that you don't need to use ./
