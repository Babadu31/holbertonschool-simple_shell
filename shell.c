#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

void free_memory(char *pointer) {
  free(pointer);
  pointer = NULL;
}

char **mystrtok(char *buf, char **args) {
  char *token = NULL;
  char *delims = " \n";
  unsigned int i = 0;

  token = strtok(buf, delims);
  while (token) {
    args[i] = token;
    token = strtok(NULL, delims);
    i++;
  }
  return (args);
}

int main(void) {
  char *buf = NULL, **args = calloc(4, sizeof(char *));
  ssize_t nread;
  size_t len = 0;
  int status = 0;
  pid_t child;

  while ((nread = getline(&buf, &len, stdin)) != -1) {
    args = mystrtok(buf, args);
	if (args == NULL)
      continue;
    child = fork();
    if (child == -1) {
      perror("Error:");
      return (1);
    }
    if (child == 0) {
      if (args[0] && execve(args[0], args, environ) == -1) {
        perror("execve");
      }
      free_memory(buf);
      free(args);
      args = NULL;
    } else {
      wait(&status);
    }
  }

  free_memory(buf);
  free(args);
  args = NULL;
  return (0);
}
