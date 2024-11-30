#!/usr/bin/env bash
# hash -d todo
# if you want the file to be totally wiped, just use the command above in your terminal
if [ -f ~/.todo_data ]; then
    rm ~/.todo_data
fi
sudo rm -i /usr/local/bin/todo
