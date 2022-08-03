#include "shell.h"

int main(void) {
	char *buf = NULL, **args = calloc(10, sizeof(char *)), cmd;
	ssize_t nread;
	size_t len = 0;
	int status = 0, i, j;
	pid_t child;

	while ((nread = getline(&buf, &len, stdin)) != -1) {
		if (buf == "\n")
		{
			free_memory(buf);
			continue;
		}
		args = split(buf, " \n");
		for(i = 0; args[i]; i++)
			printf("%s\n", args[i]);
		if (args == NULL)
			continue;
		path_handler(args);
		child = fork();
		if (child == -1) {
			perror("Error:");
			return (1);
		}
		if (child == 0) {
			if (args[0] && execve(args[0], args, environ) == -1) {
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free_array_memory(args);
			free_memory(buf);
		} else {
			wait(&status);
		}
	}
	free_array_memory(args);
	args = NULL;
	free_memory(buf);
	buf = NULL;
	return (0);
}
