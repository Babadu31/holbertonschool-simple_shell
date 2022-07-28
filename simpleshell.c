#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - function
 *
 * Return: 
 */

int main(int argc, char **argv, char **env)
{
  size_t len;
  char *buf;
  char *token;
  int status;
  pid_t child;

  while(1)
    {
      buf = NULL;
      child = fork();
      if (child == 0)
	{
	  write(STDOUT_FILENO, "#cisfun$ ", 10);
	  while (getline(&buf, &len, stdin) != -1)
	    {
	      token = strtok(buf, "\n");
	      if (execve(token, argv, env) == -1)
		perror("./simpleshell");
	      write(STDOUT_FILENO, "#cisfun$ ", 10);
	    }
	  free(buf);
	  return (0);
	}
      else
	{
	  wait(&status);
	}
    }
  return (0);
}
