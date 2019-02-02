# CS 100 Programming Project

Product Information
> Author(s): Darrien Gunn (862030886), Christian Lee (862053682)
> Winter 2019

## Introduction
We will be developing a command shell (Rshell) in C++ that will be able to print command prompts, read in commands and connectors from standard input, and execute the appropriate commands using _execvp_, _waitpid_, and _fork_. A shell is a user interface which accesses an operating system’s services. Specific characters (commands) will be used to provide instructions and send data to the operating system. 

Rshell will be able to handle inputs without limit to the number of commands chained together through connections as well as any combination of operators. Since this program is structural/object focused, we will use composite pattern to represent the hierarchies of our classes. 

Following the **composite** design pattern, our composite class will be the Connector class along with a leaf class called Operator.

## Diagram

![example expression tree](/images/Composite.png?raw=true "Diagram")
      
## Classes
* Root directory: Contains files (README.md, src/, tests/, CMakeLists.txt)
src/
* Base class: Abstract type which oversees the previous command that was output and leaves execute and check functions to be defined in child classes.
* Connector class: Composite class which inherits from Rshell and contains the connectors And, Or, Semicolon.
* Op class: Leaf class that inherits from the base class where each object holds a single command to execute.
* And class: Inherited class where objects represent a connector within a line of input and holds one command. Command will only execute if the previous command was a success.
* Or class: Inherited class where objects represent a connector within a line of input and holds one command. Command will only execute if the previous command fails.
* Semicolon class: Inherited class where objects represent a connector within a line of input and holds one command. Command will always execute regardless of the success or failure of the previous command. The first command in a list of commands is always from the Semicolon class.
* tests/
* Test.cpp: Google testing framework


## Prototypes/Research

Main for implementing fork, getpid, and execvp.

```c++
int main() {
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1){
        // error, failed to fork()
    } 
    else if (pid > 0){
        int status;
        waitpid(pid, &status, 0);
    }
    else {
        // we are the child
        execvp(...);
        _exit(EXIT_FAILURE);   // exec never returns
    }
}
```
**Create composite for command operators**.
* For “;”, the next command is always executed.
* For “||”, If the first command fails, execute the next command.
* For “&&”, If the first command succeeds, execute the next command.
* For “exit”, the rest of the command line is ignored.
* For “#”, the rest of the command line is entered as a comment.

Every *syscall*, errors should be checked and perror should be called if an error does occur.
Creating folder “src/” for all source files. Header files can be kept in the same folders or their own header folder. A “unit_tests/” directory should exist for all the unit test for all the Google Unit Testing framework. The main test file can be in this folder or the “src”. An “Integration_tests/” directory should also contain all the integration test. The root directory must also include two targets, the rshell, which should build the main executable, and the test which should run the unit test that have been created using the Google Unit Test Framework. Any temp files and machine specific files should be added to the .gitignore.

## Development and Testing Roadmap
Development will be carried out with continued communication and collaboration
Plan out and agree upon our objective and approach towards utilizing fork, waitpid, and execvp
Christian: Responsible for Base, Op, Connector classes
Darrien: Responsible for And, Or, Semicolon classes
Implement test cases together and review each other’s work 
Integrate divided work by merging branches on Github once agreed upon



