#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * free_memory - func to free
 * @pointer: pointer
 * Return: void
 */

void free_memory(char *pointer)
{
	free(pointer);
	pointer = NULL;
}

/**
 * mystrtok - func to strtok
 * @buf: buffer
 * Return: args
 */

char **mystrtok(char *buf)
{
	char *token = NULL, **args = calloc(500, sizeof(char *));
	char *delims = " \n";
	unsigned int i = 0;

	token = strtok(buf, delims);
	while (token)
	{
		args[i] = token;
		token = strtok(NULL, delims);
		i++;
	}
	return (args);
}

/**
 * main - main func
 * Return:0
 */

int main(void)
{
	char *buf = NULL, *token, *delims = " \n", **args = NULL;
	ssize_t nread;
	size_t len = 0;
	int b = 0, status = 0;
	pid_t child;

	while ((nread = getline(&buf, &len, stdin)) != -1)
	{
		args = mystrtok(buf);
		child = fork();
		if (child == 0)
		{
			if (args[0] && execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				free_memory(buf);
				free(args);
				args = NULL;
				exit(EXIT_FAILURE);
			}
		} else if (child == -1)
			exit(0);
		else
			wait(&status);
	}
	free_memory(buf);
	free(args);
	args = NULL;
	return (0);
}
