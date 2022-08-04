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
	char **args = NULL;

	while ((nread = getline(&buf, &len, stdin)) != -1)
	{
		args = split(buf, del);
		if (args == NULL || args[0] == NULL)
			continue;
		/*path_handler(args);*/
		child = fork();
		if (child == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child == 0)
		{
			if (args[0] && execve(args[0], args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free_array_memory(args);
			free_memory(buf);
		} else
			wait(&status);
	}
	/*free_array_memory(path_array);
	free_array_memory(args);
	free_memory(buf);*/
	return (0);
}
