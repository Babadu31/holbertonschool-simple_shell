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
	char *token = NULL;
	char **args = NULL;
	int i = 0;

	token = strtok(buf, del);
	while (token)
	{
		args = realloc(args, ((i + 1) * sizeof(char *)));
		args[i] = strdup(token);
		token = strtok(NULL, del);
		++i;
	}
	args = realloc(args, ((i + 1) * sizeof(char *)));
	args[i] = NULL;
	return (args);
}
