#include "shell.h"

/**
 * free_array_memory - free pointers of pointers
 * @array: pointer of pointers
 *
 */

void free_array_memory(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

/**
  * free_memory - free pointer
  * @pointer: pointer
  *
  */

void free_memory(char *pointer)
{
	free(pointer);
	pointer = NULL;
}

/**
 * split - function to split line buffer to command + arguments
 * @buf: buffer
 * @del: delimiters
 *
 * Return: array full of pointers to command + arguments
 */

char **split(char *buf, char *del)
{
	int bufsize = S_SHELL_BUFSIZE;
	char **args = malloc(bufsize * sizeof(char*));
	char *token;
	int i = 0;

	token = strtok(buf, del);
	while (token)
	{
		args[i] = token;
		++i;
		if (i >= bufsize)
		{
			bufsize += S_SHELL_BUFSIZE;
			token = realloc(token, bufsize * sizeof(char*));
			if (!token)
			{
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, del);
	}
	args[i] = NULL;
	return args;
}
