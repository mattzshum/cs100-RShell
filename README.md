# CS 100 Programming Project

Product Information
> Author(s): Matthew Shum (862009656), Christian Lee (862053682)
> Winter 2019

## Introduction
We will be developing a command shell (Rshell) in C++ that will be able to print command prompts, read in commands and connectors from standard input, and execute the appropriate commands using _execvp_, _waitpid_, and _fork_. A shell is a user interface which accesses an operating system’s services. Specific characters (commands) will be used to provide instructions and send data to the operating system. 

Rshell will be able to handle inputs without limit to the number of commands chained together through connections as well as any combination of operators. Since this program is structural/object focused, we will use composite pattern to represent the hierarchies of our classes. Our program will make sure to take precedence i.e. parentheses into account when reading in different commands along with their connectors. Rshell will also be able to handle test commands [ ] with flags (-e, -f, -d). Through the utilization of dup, dup2, and pipe, Rshell will allow for the redirection of inputs, outputs, and double outputs.

Following the **composite** design pattern, our composite class will be the *Connector* class along with a *leaf* class called Operator.

## Diagram

![example expression tree](images/Assignment%201%20UML.png?raw=true "Diagram")
      
## Classes
* Root directory: Contains files (README.md, src/, unit_tests/, integration_test/, CMakeLists.txt)
* src/
  * Base class: Abstract type which oversees the previous command that was output and leaves execute and check functions to be defined in child classes.
  * Command class: Composite class that inherits from the base class where each object holds a single command to execute.
  * NormCommand class : Inherited class where objects represent the basic "normal" commands that would be executed through the shell program.
  * TestCommand class : Inherited class where objects represent the test commands that will be exectued as linux system based calls with flags *e, f,* and *d*.
  * Connector class: Composite class which inherits from Rshell and contains the connectors And, Or, Semicolon.
  * And class: Inherited class where objects represent a connector within a line of input and holds one command. Command will only execute if the previous command was a success.
  * Or class: Inherited class where objects represent a connector within a line of input and holds one command. Command will only execute if the previous command fails.
  * Semicolon class: Inherited class where objects represent a connector within a line of input and holds one command. Command will always execute regardless of the success or failure of the previous command. The first command in a list of commands is always from the Semicolon class.
  * InputRedirect class : Inherited class of Connector which handles input to be redirected from a file.
  * OutputRedirect class : Inherited class of Connector which handles output to be redirected to a file rather than standard output.
  * DoubleOutput class : Inherited class of Connector which handles output to be redirected to a file rather than standard output while appending that output to a file.
  * Pipe class : Inherited class of Connector which allows the redirection of one command/process into another command/process.
  * Rshell class: Leaf class to handle the parsing of commands and build the structural design of commands read in for execution. 
* unit_tests/
  * unit_test.cpp: Google testing framework
* integration_tests/
  * Contains integration_tests.sh files for the different functions we will be taking

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

> Note: For every *syscall*, errors should be checked and perror should be called if an error does occur.

**Creating files, folders, and directories**
* Creating folder “src/” for all source files. 
* Header files can be kept in the same folders or their own header folder.
* A “unit_tests/” directory should exist for all the unit test for all the Google Unit Testing framework. 
* An “Integration_tests/” directory should also contain all the integration test. 
* The root directory must also include two targets, the rshell, which should build the main executable, and the test which should run the unit test that have been created using the Google Unit Test Framework. 
* Any temp files and machine specific files should be added to the .gitignore.
* Contain file including names, SIDs, and emails of group members

> Note: Main test file can be in "unit_test/" or "src/"

**Creating helper functions for implementation**
* Parsing: Parsing will be done by storing input line within a queue. Elements will be separated through the use of *tokenizer* which we will then further divide based on commands and connectors. This will be achieved through the use of substrings to sort the contents of the string queue.
* Recursive Parsing: We will use parse recursively in order to take cases involving parentheses into account for precedence. This will allow us to handle commands along with their connectors and prioritize their execution before the execution of the rest of the command line.

**Creating and implementing flags for test commands**
* - e : checks if the file/directory exists
* - f : checks if the file/directory exists and is a regular file
* - d : checks if the file/directory exists and is a directory
* Commands executed correctly will return *(True)*.
* Commands executed incorrectly will return *(False)*.

**Add pipe, input redirection, output redirection, and double output redirection connectors**
* - pipe : redirection to send the output of one command/process to another command/process for execution
* - input redirection : takes in input and is redirected by calling "<"
* - output redirection : takes in output from a file and is redirected by calling ">"
* - double output redirection : takes in output and appends to a file by calling ">>"

## Development and Testing Roadmap
* Development will be carried out with continued communication and collaboration
* Plan out and agree upon our objective and approach towards utilizing fork, waitpid, and execvp
* Team members will utilize time most effectively through meeting up and actively communicating/designing/implementing. This ensures that work will be accomplished onto with any and all issues being addressed immediately.
* Remain in contact throughout the course of program implementation to keep track of progress.
* Coding will be done remotely as well as in person to optimize work flow.
* Implement test cases together and review each other’s work 
* Integrate divided work by merging branches on Github once agreed upon



