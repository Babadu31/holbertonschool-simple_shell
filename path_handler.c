#include "shell.h"

void path_handler(char **args) {
	char *path = strdup(getenv("PATH"));
	char *mem = NULL;
	char **splitor = NULL;

	// create the path if it doesn't exist

	if (path == NULL)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	//Check if the path is include in the command writed and if not go fetch all the path that exists

	if (args[0][0] != '/') {
		splitor = split(path, ":");

		free_memory(path);

		// Check if the command written is present in one of the path 

		for (int i = 0; splitor[i]; i++) {
			mem = (char *)calloc(sizeof(char), (strlen(splitor[i]) + 1 + strlen(args[0]) + 1));
			if (mem == NULL)
				break;

			//Concatenate the path before the command    

			strcat(mem, splitor[i]);
			strcat(mem, "/");
			strcat(mem, args[0]);

			//Check if it can acces the command with the path and if not free all

			if (access(mem, F_OK) == 0)
				break;

			free_memory(mem);
		}
		free_array_memory(splitor);
		free_memory(args[0]);

		//Redefine the command pointer to the adress of the command with the path in it so the execve can execute the command properly

		args[0] = realloc(args[0], sizeof(mem));
		args[0] = mem;

	} 
	else
		free_memory(path);
}
