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

char **split(char *buf, char *del, char **args)
{
	int i = 0;
	char *token;

	token = strtok(buf, del);
	while (token)
	{
		args[i] = token;
		token = strtok(NULL, del);
		++i;
	}
	args[i] = NULL;
	return args;
}
