/*
Created by Shane Kennedy
Version 4
Debugging redirection of STANDARD OUTPUT
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX 64

void processRunner(pid_t pid1, char **token, int counter)
{
  if(counter == 4)
  {
    pid1 = getpid();
    execlp(token[3], token[2], token[1], token[0], NULL);
    printf("Running (Pid: %d)", pid1);
    printf(" %s %s %s %s\n", token[3], token[2], token[1], token[0]);
  }
  else if(counter == 3)
  {
    pid1 = getpid();
    execlp(token[2], token[1], token[0], NULL);
    printf("Running (Pid: %d)", pid1);
    printf(" %s %s %s\n", token[2], token[1], token[0]);
  }
  else if(counter == 2)
  {
    pid1 = getpid();
    execlp(token[1], token[0], NULL);
    printf("Running (Pid: %d)", pid1);
    printf(" %s %s\n", token[1], token[0]);
  }
  else if(counter == 1)
  {
    pid1 = getpid();
    execlp(token[0], token[0], NULL);
    printf("Running (Pid: %d)", pid1);
    printf(" %s\n", token[0]);
  }
}

int main()
{
  int run = 1;
  pid_t pid, pid1;
  //while loop to output and take in commands
  while(run == 1)
  {
    char buffer[MAX];
    char **token;
    char *args[MAX];
    int counter = 0;
    bool flag = false;
    bool redirect = false;
    int fd;
    int saved_stdout = dup(1);

    //prompt output
    printf("skenne5> ");
    //get output
    fgets(buffer, MAX, stdin);
    token = args;
    //tokenize inputs
    *token++ = strtok(buffer, " \n");
    while(*token++ = strtok(NULL, " \n"))
      counter++;
    counter++;  //counter is incremented an extra time to get correct number of tokens

    //check if anything was typed in
    if(args[0])
    {
      token = args;
      for(int i = 0; i < counter; i++)
      {
        if(!strcmp(token[i], "<<"))
        {
          redirect = true;
          fd = open(args[i-1], O_WRONLY | O_CREAT, 0666);
          if(fd < 0)
          {
            printf("File Descriptor failed");
            run = 0;
          }
          dup2(fd, 1);
        }
        if(redirect == true)
        {
          if(i+1 != counter)
          {
            printf("hello");
            strcpy(token[i], token[i+1]);
            printf("words : %s\n", args[i]);
          }
        }
      }
      //check if quit is entered
      if(!strcmp(args[0], "exit"))
      {
        run = 0;
        printf("Terminating Process - if a command input did not meet requirements to run, exit may need to be run multiple times\n");
      }
      else if(!strcmp(args[0], "fg"))
      {
        pid1 = getpid();
        execlp("fg", "fg", NULL);
      }
      else if(!strcmp(args[0], "&"))
      {
        flag = true;
      }
      else
      {
        //create fork for child process
        pid = fork();

        if(pid < 0)   //error occurred
        {
          fprintf(stderr,"Fork Failed");
          exit(-1);
        }
        else if(pid == 0 && flag == false)  //child process
        {
          processRunner(pid1, token, counter);
        }
        else   //parent process
        {
          if(flag == true)
          {
            processRunner(pid1, token, counter);
          }
          wait(NULL);
        }
      }
    }
    else
    {
      printf("no input provided\n");
    }
    dup2(saved_stdout, 1);
    close(saved_stdout);
  }
  return 1;
}
