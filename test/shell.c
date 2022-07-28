#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

// Greeting shell during startup
void init_shell()
{
  clear();
  printf("\n\n\n\n******************"
	 "************************");
  printf("\n\n\n\t****SHELL****");
  printf("\n\n\t******************");
  printf("\n\n\n\n*******************"
	 "***********************");
  char* username = getenv("USER");
  printf("\n\n\nUSER is: @%s", username);
  printf("\n");
  sleep(3);
  clear();
}

// Function to take input
int takeInput(char* str)
{
  char* buf;

  buf = readline("\n>>> ");
  if (strlen(buf) != 0) {
    add_history(buf);
    strcpy(str, buf);
    return 0;
  } else {
    return 1;
  }
}


int main()
{
  char inputString[MAXCOM], *parsedArgs[MAXLIST];
  char* parsedArgsPiped[MAXLIST];
  int execFlag = 0;
  init_shell();

  while (1) {
    // print shell line
    // take input
    if (takeInput(inputString))
      continue;
    // execflag returns zero if there is no command
    // or it is a builtin command,
    // 1 if it is a simple command
    // 2 if it is including a pipe.

  return 0;
}
}
