#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - getline function
 * @ac: num of arg
 * @av: array of arg
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line;
	ssize_t read;
	size_t len;
	char *args;

	while ((read = getline(&line, &len, stdin)) != -1)
	{
		args = strtok(line, " ");
		while (args)
		{
			printf("%s\n", args);
			args = strtok(NULL, " ");
		}
		printf("$ ");
	}
	if (line)
		free(line);
	return (0);
}
