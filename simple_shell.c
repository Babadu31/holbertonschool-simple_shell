#include "shell.h"

/**
 * main - main function
 *
 * Return: End status
 */

int main(void)
{
	ssize_t nread;
	size_t len = 0;
	int status = 0;
	pid_t child;
	char *del = " \n";
	char *buf = calloc(64, sizeof(char));
	char **args = calloc(64, sizeof(char));
	char **path_array = calloc(64, sizeof(char));

	while ((nread = getline(&buf, &len, stdin)) != -1)
	{
		args = split(buf, del, args);
		if (args == NULL || args[0] == NULL)
			continue;
		path_handler(args, path_array);
		child = fork();
		if (child == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child == 0)
		{
			if (args[0] && execve(args[0], args, path_array) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free_array_memory(path_array);
			free_array_memory(args);
			free(buf);
		} else
			wait(&status);
	}
	free_array_memory(path_array);
	free_array_memory(args);
	free(buf);
	return (0);
}
