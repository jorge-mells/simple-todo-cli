# About

This is the first project I implemented using just and command line and vim. Of course I also used a browser to help me navigate the cmd. It is a simple cli todo app written in C. The primary aim of this project is to learn how to use the command line.

## Steps involved

So firstly, I created a new directory in cli. Then using git cli, I initialised the project. Finally, I used github cli to put the project on github. To use github cli, make sure you have setup your git user settings. Then get an ssh key. Go online to find out how to do that. Then you can run gh auth login to authenticate the user. finally you can run gh auth setup-git to allow seamless communication between git and github.

# How to install the project

Please note that this only works for linux users. For non linux users, just use linux, or install wsl to run this app. (I have no idea why you even want to use this app)

To install this project simply clone the project and open the folder in a web browser locally where you can display all pages.

```
git clone https://github.com/jorge-mells/simple-todo-cli.git
./install.sh

```
To uninstall use
```
./uninstall.sh
```

# Example Usage

Use `todo --help` to display most of the help info to help you use the app. 

```
todo --name "new todo" --description "example todo"
todo --list
id priority status name description
0  0  -1  new todo  example todo 
```

# License

[LICENSE](LICENSE.md)

# How to contribute

Simply fork this project and open a pull request with your changes if you want to contribute. See [CONTRIBUTING](CONTRIBUTING.md) for more information.

