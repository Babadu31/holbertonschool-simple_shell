#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - dddd
 * @argv: dsdd
 * @argc: dsqdd
 * @env: sdsd
 * Return: ffd
 */

int main(int argc, char **argv, char **env)
{
	size_t len = 0;
	char *buf = 0;
	char *token = 0;
	int status = 0, i = 0;
	pid_t child = 0;
	char **aargs = malloc(sizeof(char**));

	while (getline(&buf, &len, stdin) != -1)
	{
		(void)argc;

		token = strtok(buf, " \n");
		for (i = 0; token != NULL; i++)
		{
			aargs[i] = token;
			aargs = (char **) realloc(aargs, (i + 1) * sizeof(char**));
			token = strtok(NULL, " \n");
		}
		printf("arg0: %s arg1: %s arg2: %s\n", aargs[0], aargs[1], aargs[2]);
		child = fork();

		if (child == 0)
		{
			if (execve(token, argv, env) == -1)
				perror("Error: ");
			return (-1);
		}
		else
			wait(&status);
	}
	free(buf);
	buf = NULL;
	return (0);
}
