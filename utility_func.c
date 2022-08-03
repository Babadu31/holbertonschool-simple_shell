#include "shell.h"

void free_array_memory(char **array) {
	int i;

	for (i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void free_memory(char *pointer) {
	free(pointer);
	pointer = NULL;
}

char **split(char *buf, char *del) {
	char *token = NULL;
	char **args = NULL;
	int i = 0;

	token = strtok(buf, del);
	while (token) {
		args = realloc(args, ((i + 1) * sizeof(char *)));
		args[i] = strdup(token);
		token = strtok(NULL, del);
		++i;
	}
	args = realloc(args, ((i + 1) * sizeof(char *)));
	args[i] = NULL;
	return (args);
}
