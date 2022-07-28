#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

// Greeting shell during startup
void init_shell()
{
  clear();
  printf("\n\n\n\n******************"
	 "************************");
  printf("\n\n\n\t****MY SHELL****");
  printf("\n\n\t-USE AT YOUR OWN RISK-");
  printf("\n\n\n\n*******************"
	 "***********************");
  char* username = getenv("USER");
  printf("\n\n\nUSER is: @%s", username);
  printf("\n");
  sleep(1);
  clear();
}

int main(int argc, char **argv, char **env)
{
  size_t len;
  char *buf;
  char *token;
  int status;
  pid_t child;


  while(getline(&buf, &len, stdin) != -1)
    {
      token = strtok(buf, "\n");

      child = fork();

      if (child == 0)
	{
	  if (execve(token, argv, env) == -1)
	    perror("./simpleshell");
	  free(buf);
	  return (0);
	}
      else
	wait(&status);
      buf = NULL;
    }
  return (0);
}
