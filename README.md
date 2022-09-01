## Funny Shell

This is code from a class I took a couple years ago where all code was developed on Linux servers.

This program was created to fulfill homework/classroom requirements, not professional development.

Old README/Explanation:

In funnyShell.c the program starts by initializing all the variables that will
be used in the program. It then prints a prompt to the console labeled as my
ULID followed by ">". After the prompt is presented to the user, the program
waits for a command given to execute. When a command is given, it is stored
in a buffer that will later be tokenized. Two tokenizing commands are done to
handle all requirements. While the second tokenizing process happens, a counter is
incremented to keep track of the number of inputs that were provided by the user
The program then checks the tokenized character array to make sure that values
were added into it. The program then checks if a user inputs "<<" for redirection
of the standard output.After this, the program then checks to see if the user
entered "exit" into the prompt command. If quit is entered, the program will
change the run variable to be zero in order to stop the while loop. It will also
output a message to the user that it is terminating the process. The program then
checks if the user entered "fg" to move the most recent process to the foreground.
If "fg" is entered, a command is run to the console to move the most recent process
to the foreground. If neither of these commands are entered, a check is done to
see if "&" is entered to run the parent and child concurrently. A flag is used
for this to make sure the correct processes run. Next a child process is created
and checked to make sure it didn't fail. Once the fork is checked, the child
process runs calling a method called processRunner. This method was created as
both the child and parent will end up using the same code if the "&" command is
given. The processRunner method checks the counter to know how many lines of code
it needs to run. Each process is similar in its code, but changes with the amount
of arguments given. First the pid is found for the process then the command given
is run through the console. Next, the pid and command are printed for the user
to see. As the last main statements, the program just outputs that no commands
were entered if the user just hit the return key.
